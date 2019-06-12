<?php

class Task extends ActiveRecord {

  const TYPE_VIDEO_ENCODING = 1;
  const TYPE_PDF_CONVERSION = 2;
  const TYPE_SCRIPT_EXEC = 3;

  const STATUS_FAILED = -10;
  const STATUS_PENDING = 0;
  const STATUS_PROCESSING = 1;
  const STATUS_COMPLETED = 10;

  const PATH = 'var/task';

  public static function add($hash) {
    $dbo = S('dbo');
    foreach ($hash as $key => &$value) {
      if (is_array($value)) {
        $value = serialize($value);
      }
    }
    $dbo->insert(T('task'), $hash);
  }

  public static function process() {
    $dbo = S('dbo');
    $rs = $dbo->query('SELECT id'
                      .' FROM '.T('task')
                      .' WHERE status='.self::STATUS_PENDING);
    foreach ($rs as $row) {
      $task = null;
      try {
        $task = Task::getInstance($row['id']);
        if ($task->status != self::STATUS_PENDING) continue ;
        $task->setAttributes(array('started_at' => Date::now()));
        $task->setStatus(self::STATUS_PROCESSING);
        if (strpos($task->callback, '::') === false) continue ;
        list ($c, $method) = explode('::', $task->callback);
        call_user_func(array($c, $method), array('task' => $task));
        $task->setAttributes(array('completed_at' => Date::now()));
        if ($task->status == self::STATUS_PROCESSING) {
          $task->setStatus(self::STATUS_COMPLETED);
        }
      }
      catch (Exception $e) { 
        if ($task instanceof ActiveRecord) {
          $task->setStatus(self::STATUS_FAILED);
          $task->setAttribute('error', $e->getMessage());
        }
        S('log')->error($e); 
      }
    }
  }

  public static function show($statuses = null, $last = null) {
    if ($statuses === null) {
      $statuses = array(self::STATUS_PENDING,
                        self::STATUS_PROCESSING);
    }
    $opts = array('filters' => array('status' => $statuses),
                  'order' => array('id' => 'asc'));
    if ($last > 0) {
      $opts['last'] = $last;
    }
    $total = 0;
    foreach (self::collect($opts) as $that) {
      echo "\n".$that->getId()."\tajout    : ".$that->inserted_at."\n\t";
      if ($that->status == self::STATUS_PROCESSING) {
        echo 'status   : en cours (depuis le '.$that->started_at.")\n";
      }
      elseif ($that->status == self::STATUS_COMPLETED) {
        echo 'status   : terminé (débuté le '.$that->started_at." et terminé le ".$that->completed_at.")\n";
        if (!empty($that->output)) {
          echo "\toutput   : ".$that->output."\n";
        }
      }
      elseif ($that->status == self::STATUS_FAILED) {
        echo 'status   : erreur (débuté le '.$that->started_at.")\n";
        if (!empty($that->error)) {
          echo "\terreur   : ".$that->error."\n";
        }
      }
      else {
        echo 'status   : en attente'."\n";
      }
      if ($that->model_id > 0 && 
          $that->record_id > 0 &&
          Item::exists($that->model_id, $that->record_id)) {
        echo "\titem     : [M:".$that->model_id."-R:".$that->record_id."] ".(string) $that->getItem()."\n";
      }
      if ($that->user_id > 0
          && Model::exists('user', $that->user_id)) {
        echo "\tuser     : ".(string) $that->getUser()."\n";
      }
      if (!empty($that->callback)) {
        echo "\tcallback : ".$that->callback."()\n";
      }
      if (!empty($that->name)) {
        echo "\tnom      : ".$that->name."\n";
      }
      if (!empty($that->input)) {
        echo "\tinput    : \n".var_export($that->input, true)."\n";
      }
      $total++;
    }
    echo 'Total : '.$total."\n";
  }


  /*  public static function execute() {
    $php_bin = Shell::PHP_BIN . ' ' . Platform::BOOTSTRAP;
    //    if (file_exists(ETC_PATH.'/php-cli.ini')) {
    //      $php_bin = Shell::PHP_BIN . ' -c ' . ETC_PATH . '/php-cli.ini ' . Platform::BOOTSTRAP;
    //      }
    $files = glob(self::PATH.'/*.task');
    if (empty($files)) return ;
    foreach ($files as $file) {
      $cmd = file_get_contents($file);
      $cmd = trim($cmd);
      //      S('log')->trace($file, __METHOD__);
      ob_end_clean();
      unlink($file);
      $pid = pcntl_fork();
      if ($pid == -1) {
        throw new Exception('fork failure');
        return ;
      } 
      if (!$pid) {
        $cmd = $php_bin.' '.$cmd;
        exec($cmd);
        break ;
      }
    }
    }*/

}