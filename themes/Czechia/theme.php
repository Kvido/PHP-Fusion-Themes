<?php
/*-------------------------------------------------------+
| PHP-Fusion Content Management System
| Copyright (C) PHP-Fusion Inc
| https://www.php-fusion.co.uk/
+--------------------------------------------------------+
| Filename: Czechia/theme.php
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

require_once INCLUDES.'theme_functions_include.php';
require_once THEME.'theme_autoloader.php';
define('THEME_BULLET', '<i class="fa fa-circle"></i>');

/**
 * Required Theme Components
 */
function render_page() {
    new CzechiaTheme\Main();
}

function opentable($title = FALSE, $class = '') {
    echo '<div class="opentable">';
    echo $title ? '<div class="title">'.$title.'</div>' : '';
    echo '<div class="'.$class.'">';
}

function closetable() {
    echo '</div>';
    echo '</div>';
}

function openside($title = FALSE, $class = '') {
    echo '<div class="openside '.$class.'">';
    echo $title ? '<div class="title">'.$title.'</div>' : '';
}

function closeside() {
    echo '</div>';
}

/**
 * Downloads
 * @param $info
 */
function render_downloads($info) {
    CzechiaTheme\Templates\Downloads::render_downloads($info);
}

/**
 * Error Page
 * @param $info
 */
function display_error_page($info) {
    CzechiaTheme\Templates\Error::display_error_page($info);
}

/**
 * Login
 * @param $info
 */
function display_loginform($info) {
    CzechiaTheme\Templates\Login::LoginForm($info);
}

function display_register_form($info) {
    CzechiaTheme\Templates\Login::RegisterForm($info);
}

/**
 * News
 * @param $info
 */
function display_main_news($info) {
    CzechiaTheme\Templates\News::display_main_news($info);
}

function render_news_item($info) {
    CzechiaTheme\Templates\News::render_news_item($info);
}

/**
 * Profile
 * @param $info
 */
function display_user_profile($info) {
    CzechiaTheme\Templates\Profile::DisplayProfile($info);
}

function display_user_field($info) {
    CzechiaTheme\Templates\Profile::Field($info);
}

function display_profile_form($info) {
    CzechiaTheme\Templates\Profile::EditProfile($info);
}

set_image('imagenotfound', fusion_get_settings('siteurl').'themes/Czechia/images/noimage.svg');

/**
 * @param string $output
 * @return mixed
 */
function replace_meta($output = '') {
    return preg_replace("/<meta name='theme-color' content='#ffffff'>/i", '<meta name="theme-color" content="#196496"/>', $output);
}

\PHPFusion\OutputHandler::addHandler('replace_meta');
