<?php
/*-------------------------------------------------------+
| PHP-Fusion Content Management System
| Copyright (C) PHP-Fusion Inc
| https://www.php-fusion.co.uk/
+--------------------------------------------------------+
| Filename: AdminLTE/classes/Components.inc
| Author: RobiNN
+--------------------------------------------------------+
| This program is released as free software under the
| Affero GPL license. You can redistribute it and/or
| modify it under the terms of this license which you
| can read by viewing the included agpl.txt or online
| at www.gnu.org/licenses/agpl.html. Removal of this
| copyright header is strictly prohibited without
| written permission from the original author(s).
+--------------------------------------------------------*/
namespace AdminLTE;

/**
 * Class Components
 * @package AdminLTE
 */
class Components {
    private static $messages = [];
    private static $breadcrumbs = FALSE;

    public static function Messages() {
        $userdata = fusion_get_userdata();

        $result = dbquery("
            SELECT message_id, message_subject, message_from user_id, u.user_name, u.user_status, u.user_avatar, message_datestamp
            FROM ".DB_MESSAGES."
            INNER JOIN ".DB_USERS." u ON u.user_id=message_from
            WHERE message_to='".$userdata['user_id']."' AND message_user='".$userdata['user_id']."' AND message_read='0' AND message_folder='0'
            GROUP BY message_id
        ");

        if (dbcount("(message_id)", DB_MESSAGES, "message_to='".$userdata['user_id']."' AND message_user='".$userdata['user_id']."' AND message_read='0' AND message_folder='0'")) {
            if (dbrows($result) > 0) {
                while ($data = dbarray($result)) {
                    self::$messages[] = [
                        'link'      => $data['message_id'],
                        'title'     => $data['message_subject'],
                        'user'      => [
                            'user_id'     => $data['user_id'],
                            'user_name'   => $data['user_name'],
                            'user_status' => $data['user_status'],
                            'user_avatar' => $data['user_avatar']
                        ],
                        'datestamp' => timer($data['message_datestamp'])
                    ];
                }
            }
        }

        return self::$messages;
    }

    public static function GetMessages() {
        return self::$messages;
    }

    public static function IsMobile() {
        return preg_match("/(android|avantgo|blackberry|bolt|boost|cricket|docomo|fone|hiptop|mini|mobi|palm|phone|pie|tablet|up\.browser|up\.link|webos|wos)/i", $_SERVER['HTTP_USER_AGENT']);
    }

    public function SetLocale($lc = NULL) {
        $locale = [];

        if (file_exists(ADMINLTE.'locale/'.LANGUAGE.'.php')) {
            include ADMINLTE.'locale/'.LANGUAGE.'.php';
        } else {
            include ADMINLTE.'locale/English.php';
        }

        return $locale['ALT_'.$lc];
    }

    public static function OpenSide($title = FALSE, $class = NULL) {
        echo '<div class="box box-widget '.$class.'">';
        echo $title ? '<div class="box-header with-border">'.$title.'</div>' : '';
        echo '<div class="box-body">';
    }

    public static function CloseSide($title = FALSE) {
        echo '</div>';
        echo $title ? '<div class="box-footer">'.$title.'</div>' : '';
        echo '</div>';
    }

    public static function OpenTable($title = FALSE, $class = NULL, $bg = TRUE) {
        if (!empty($title)) {
            echo '<section class="content-header">';
            echo '<h1>'.$title.'</h1>';

            if (self::$breadcrumbs == FALSE) {
                echo render_breadcrumbs();
                self::$breadcrumbs = TRUE;
            }
            echo '</section>';
        }

        echo '<section class="content '.$class.'">';

        if ($bg == TRUE) echo '<div class="p-15" style="background-color: #fff;">';
    }

    public static function CloseTable($bg = TRUE) {
        if ($bg == TRUE) echo '</div>';
        echo '</section>';
    }
}
