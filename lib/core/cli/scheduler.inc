<?php

$php_bin = Shell::PHP_BIN . ' ' . Platform::BOOTSTRAP;
/*if (file_exists(ETC_PATH.'/php-cli.ini')) {
  $php_bin = Shell::PHP_BIN . ' -c ' . ETC_PATH . '/php-cli.ini ' . Platform::BOOTSTRAP;
  }*/

$failures = 0;

if (CLUSTER_NODE_ID > 1) {
  $actions = array('session.clean', 'cache.clean', 'log.rotate');
  foreach ($actions as $action) {
    $cmd = $php_bin.' '.$action;
    system($cmd, $ret);
    if ($ret == Platform::EXIT_STATUS_FAILURE) {
      $failures++;
    }
  }
  if ($failures > 0) {
    Mail::alarm('scheduled task error : cluster node : '.CLUSTER_NODE_ID);
  }
  return ;
}

if (!is_dir(Scheduler::PATH)) {
  mkdir(Scheduler::PATH);
}

$ts = time();

$files = glob(Scheduler::PATH.'/*.safe');
$files = $files ? $files : array();
$ttl = 2 * 24 * 60 * 60;
foreach ($files as $file) {
  if (!file_exists($file)) continue ;
  $fts = filemtime($file);
  if (($ts - $fts) > $ttl) {
    unlink($file);
  }
}

$files = glob(Scheduler::PATH.'/*.log');
$files = $files ? $files : array();
$n = count($files);
if ($n >= 2) {
  $msg = 'too many scheduled processes queued ('.$n.')';
  Mail::alarm($msg);
  $log->error($msg);
}

$log_file = Scheduler::PATH.'/'.date('Y-m-d-H-i-s').'.log';

touch($log_file);

$periods = array('hourly');


if (date('G') == 3) {
  $periods[] = 'daily';
  if (date('w') == 1) {
    $periods[] = 'weekly';
  }
  if (date('j') == 1) {
    $periods[] = 'monthly';
    if (date('n' == 1)) {
      $periods[] = 'yearly';
    }
  }
}
elseif (date('G') == 12) {
  $periods[] = 'middaily';
}

//$log->debug($periods);

$executed_jobs = array();

foreach ($periods as $period) {
  $scheduled_jobs = array();
  foreach (glob('lib/*/cli/cron.'.$period.'/*') as $path) {
    if (preg_match('/(\.LCK|~|\.bak|\.safe|\.old)$/i', $path)) continue ;
    $job = basename($path);
    $scheduled_jobs[$path] = intval(substr($job, 0, 2));
  }
  asort($scheduled_jobs);

  $content = join("\n", array_keys($scheduled_jobs)).Scheduler::SEPARATOR;
  file_put_contents($log_file, $content, FILE_APPEND);

  //  S('log')->debug($scheduled_jobs);

  foreach ($scheduled_jobs as $path => $priority) {
    if (file_exists('scheduler.stop')) {
      Mail::alarm('scheduler.stop found');
      $log->error('blocker file found');
      return ;
    }
    list (, $extension, , , $job) = explode('/', $path);
    $job = substr($job, 2);
    $script = LIB_PATH.'/'.$extension.'/cli/'.$job.'.inc';
    $action = $extension.'/'.$job;
    if (in_array($script, $executed_jobs)) {
      continue ;
    }
    $load = sys_getloadavg();
    $content = join("\t",
                    array(date('Y-m-d H:i:s'),
                          join(',', $load),
                          $period,
                          $extension,
                          $job));
    file_put_contents($log_file, $content, FILE_APPEND);
    $status = 'success';
    $start_ts = time();
    if (!file_exists($script)) {
      $status = 'failure';
      $log->trace('script not found ['.$path.']');
    }
    else {
      $executed_jobs[] = $script;
      //include $script;
      $ret = 0;
      $cmd = $php_bin.' '.$action;
      system($cmd, $ret);
      if ($ret == Platform::EXIT_STATUS_FAILURE) {
        $failures++;
        $status = 'failure';
      }
    }
    $duration = time() - $start_ts;
    $content = "\t".join("\t",
                         array($duration,
                               $status,
                               "\n"));
    file_put_contents($log_file, $content, FILE_APPEND);
  }
  $load = sys_getloadavg();
  $content = join("\t",
                  array(date('Y-m-d H:i:s'),
                        join(',', $load),
                        'end',
                        Scheduler::SEPARATOR));
  file_put_contents($log_file, $content, FILE_APPEND);
}

if ($failures > 0) {
  Mail::alarm(file_get_contents($log_file));
}

rename($log_file, substr($log_file, 0, -3).'safe');