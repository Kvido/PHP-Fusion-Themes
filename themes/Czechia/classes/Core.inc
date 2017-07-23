<?php
/*-------------------------------------------------------+
| PHP-Fusion Content Management System
| Copyright (C) PHP-Fusion Inc
| https://www.php-fusion.co.uk/
+--------------------------------------------------------+
| Filename: Czechia/classes/Core.inc
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
namespace CzechiaTheme;

/**
 * Class Core
 * The core of the theme
 *
 * @package CzechiaTheme
 */
class Core {
    private static $options = [
        'right'   => TRUE,
        'header'  => TRUE,
        'footer'  => TRUE,
        'notices' => TRUE
    ];

    /**
     * @param null $name
     * @return mixed
     */
    protected static function GetParam($name = NULL) {
        if (isset(self::$options[$name])) {
            return self::$options[$name];
        } else {
            print_p($name);
            debug_print_backtrace();
        }
    }

    /**
     * @param $name
     * @param $value
     */
    public static function SetParam($name, $value) {
        self::$options[$name] = $value;
    }

    /**
     * @param null $key
     * @return mixed
     */
    public static function SetLocale($key = NULL) {
        $locale = [];

        if (file_exists(THEME.'locale/'.LANGUAGE.'.php')) {
            include THEME.'locale/'.LANGUAGE.'.php';
        } else {
            include THEME.'locale/English.php';
        }

        return $locale[$key];
    }

    /**
     * Copyright
     */
    public static function ThemeCopyright() {
        echo '<strong>'.self::SetLocale('pfc_title').' &copy; '.date('Y').' '.self::SetLocale('created_by');
        echo ' <a href="https://github.com/RobiNN1" target="_blank">RobiNN</a></strong>';
    }
}
