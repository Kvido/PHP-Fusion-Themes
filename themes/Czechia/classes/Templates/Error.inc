<?php
/*-------------------------------------------------------+
| PHP-Fusion Content Management System
| Copyright (C) PHP-Fusion Inc
| https://www.php-fusion.co.uk/
+--------------------------------------------------------+
| Filename: Czechia/classes/Templates/Error.inc
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
namespace CzechiaTheme\Templates;

use CzechiaTheme\Core;
use CzechiaTheme\Main;
use \PHPFusion\Panels;

/**
 * Class Error
 *
 * @package CzechiaTheme\Templates
 */
class Error extends Core {
    public static function display_error_page($data) {
        $locale = fusion_get_locale();

        add_to_head('<style type="text/css">
            body {
                background: #0077C0;
                color: #fff;
            }
            .wrapper {
                margin: 50px auto;
                max-width: 600px;
            }
            .logo {
                max-height: 120px;
            }
            .status {
                font-size: 5em;
            }
            @media (min-width: 400px) {
                .status {
                    font-size: 7em;
                }
            }
            @media (min-width: 768px) {
                .status {
                    font-size: 10em;
                }
            }
        </style>');

        Main::HideAll();

        $locale['error'] = str_replace('!', '', $locale['error']);
        set_title($locale['error'].' '.$data['status']);

        echo '<div class="wrapper">';
            echo '<div class="logo">';
                echo '<a href="'.BASEDIR.fusion_get_settings('opening_page').'" title="'.fusion_get_settings('sitename').'">';
                    echo '<img src="'.fusion_get_settings('siteurl').'/'.fusion_get_settings('sitebanner').'" class="logo center-x" alt="Logo"/>';
                echo '</a>';
            echo '</div>';

            echo '<div class="text-center">';
                echo '<h1 class="status">'.$data['status'].'</h1>';
                echo '<h2 class="title">'.$data['title'].'</h2>';
            echo '</div>';
        echo '</div>';
    }
}
