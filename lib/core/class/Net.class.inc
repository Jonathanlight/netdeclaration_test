<?php

class Net
{
  const PROTOCOL_HTTP = 'HTTP';
  
  public static function ping($ip, $port, $timeout=1) {
    $fp = @fsockopen($ip, $port, $errno, $errstr, $timeout);
    if ($fp === false) return false;
    fclose($fp);
    return true;
  }
  
  public static function isPrivateAddress($address) {
    if (strpos($address, '.') === false) return true;
    return $address === '127.0.0.1' ||
           preg_match('/^(10|172\.(1[6-9]|2[0-9]|30|31)|192\.168)\./', $address) >= 1;
  }

  public static function ip2country($ip, $return_code=false) {
    $ret = (int) S('dbo')->fetchValue('SELECT '.($return_code === true ? 'code' : 'country_id')
                                      .' FROM sys_country_ip'
                                      .' WHERE from_ip <= inet_aton(:ip:) AND to_ip >= inet_aton(:ip:)',
                                      array(':ip:' => $ip));
    return $ret < 1 ? Country::FR : $ret;
  }

  public static function dnsblquery($ip) {
    $ip_reverse = join('.', array_reverse(explode('.', $ip)));
    foreach (array('zen.spamhaus.org', 'list.dsbl.org') as $dns) {
      if (checkdnsrr($ip_reverse.'.'.$dns, 'A')) return $dns;
    }
    return false;
  }

  public static function isOpenedPort($ip, $port, $timeout=3) {
    $fp = fsockopen($ip, $port, $errno, $errstr, $timeout);
    if (!$fp) return false;
    fclose($fp);
    return true;
  }

  public static function ip2num($ip) {
    return sprintf('%u', ip2long($ip));
  }

  public static function num2ip($num) {
    return long2ip($num);
  }

  public static function ip2host($ip) {
    return gethostbyaddr($ip);
  }


  
}


/*

function ping($host) {
    $package = "\x08\x00\x19\x2f\x00\x00\x00\x00\x70\x69\x6e\x67";

    // create the socket, the last '1' denotes ICMP  
    $socket = socket_create(AF_INET, SOCK_RAW, 1);
   
    // set socket receive timeout to 1 second 
socket_set_option($socket, SOL_SOCKET, SO_RCVTIMEO, array("sec" => 1, "usec" => 0));

// connect to socket 
socket_connect($socket, $host, null);

// record start time 
list($start_usec, $start_sec) = explode(" ", microtime());
$start_time = ((float) $start_usec + (float) $start_sec);

    socket_send($socket, $package, strlen($package), 0);

    if(@socket_read($socket, 255)) {
        list($end_usec, $end_sec) = explode(" ", microtime());
        $end_time = ((float) $end_usec + (float) $end_sec);
   
        $total_time = $end_time - $start_time;
       
        return $total_time;
    } else {
        return false;
    }
   
    socket_close($socket);
}

*/