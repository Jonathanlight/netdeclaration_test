<?php

Shell::exec('mysqldump '.DB_NAME.' -r db.sql');
Shell::exec('ls -lah db.sql');

