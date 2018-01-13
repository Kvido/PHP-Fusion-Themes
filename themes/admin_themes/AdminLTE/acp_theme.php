<?php
/*-------------------------------------------------------+
| PHP-Fusion Content Management System
| Copyright (C) PHP-Fusion Inc
| https://www.php-fusion.co.uk/
+--------------------------------------------------------+
| Filename: AdminLTE/acp_theme.php
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

define('ADMINLTE', THEMES.'admin_themes/AdminLTE/');
require_once INCLUDES.'theme_functions_include.php';
require_once ADMINLTE.'acp_autoloader.php';

define('BOOTSTRAP', TRUE);
define('FONTAWESOME', TRUE);

if (fusion_get_settings('version') != '9.0') {
    if (!check_admin_pass('')) {
        define('THEME_BODY', '<body class="hold-transition lockscreen">');
    } else {
        define('THEME_BODY', '<body class="hold-transition skin-blue sidebar-mini">');
    }
} else {
    if (!check_admin_pass('')) {
        add_to_jquery('if (!$("body").hasClass("hold-transition") || !$("body").hasClass("lockscreen")) {$("body").addClass("hold-transition lockscreen");}');
    } else {
        add_to_jquery('if (!$("body").hasClass("hold-transition") || !$("body").hasClass("skin-blue")) {$("body").addClass("hold-transition skin-blue sidebar-mini");}');
    }
}

\PHPFusion\Admins::getInstance()->setAdminBreadcrumbs();

function render_admin_panel() {
    new AdminLTE\AdminPanel();
}

function render_admin_login() {
    new AdminLTE\Login();
}

function render_admin_dashboard() {
    AdminLTE\Dashboard::AdminDashboard();
}

function openside($title = FALSE, $class = NULL) {
    AdminLTE\Components::OpenSide($title, $class);
}

function closeside($title = FALSE) {
    AdminLTE\Components::CloseSide($title);
}

function opentable($title, $class = NULL, $bg = TRUE) {
    AdminLTE\Components::OpenTable($title, $class, $bg);
}

function closetable($bg = TRUE) {
    AdminLTE\Components::CloseTable($bg);
}

\PHPFusion\OutputHandler::addHandler(function ($output = '') {
    $color = !check_admin_pass('') ? 'd2d6de' : '3c8dbc';

    return preg_replace("/<meta name='theme-color' content='#ffffff'>/i", '<meta name="theme-color" content="#'.$color.'"/>', $output);
});
