<?php
/*-------------------------------------------------------+
| PHP-Fusion Content Management System
| Copyright (C) PHP-Fusion Inc
| https://www.php-fusion.co.uk/
+--------------------------------------------------------+
| Filename: Czechia/theme_db.php
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
if (!defined('IN_FUSION')) {
    die('Access Denied');
}

if (file_exists(THEMES.'Czechia/locale/'.LANGUAGE.'.php')) {
    $locale = fusion_get_locale('', THEMES.'Czechia/locale/'.LANGUAGE.'.php');
} else {
    $locale = fusion_get_locale('', THEMES.'Czechia/locale/English.php');
}

$theme_title       = $locale['pfc_title'];
$theme_description = $locale['pfc_description'];
$theme_screenshot  = 'preview.png';
$theme_author      = 'RobiNN';
$theme_web         = 'https://github.com/RobiNN1';
$theme_license     = 'AGPL3';
$theme_version     = '1.5';
$theme_folder      = 'Czechia';
