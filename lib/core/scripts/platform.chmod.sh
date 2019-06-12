#!/bin/sh

find . -type d -exec chmod 755 {} \;
find . -type f -exec chmod 644 {} \;
find lib/shop/opt/ips -type f -exec chmod 111 {} \;
find lib/shop/opt/ips -type f -name "*.*" -exec chmod 644 {} \;
find mysql -type f -exec chmod 660 {} \;
chmod 400 init.php