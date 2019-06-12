<?php

$dbo->exec('DELETE FROM '.Act::TABLE
           .' WHERE (TO_DAYS(:now:) - TO_DAYS(created_at)) > 183'
           .  ' AND type<'.Act::TYPE_REMOVE, 
           array(':now:' => Date::now()));

$dbo->exec('DELETE FROM '.Sender::TABLE_QUEUE
           .' WHERE (TO_DAYS(:now:) - TO_DAYS(created_at)) > 7', 
           array(':now:' => Date::now()));

$dbo->exec('DELETE FROM '.Smtp::TABLE
           .' WHERE (TO_DAYS(:now:) - TO_DAYS(created_at)) > 183', 
           array(':now:' => Date::now()));
