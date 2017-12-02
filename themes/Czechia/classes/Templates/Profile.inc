<?php
/*-------------------------------------------------------+
| PHP-Fusion Content Management System
| Copyright (C) PHP-Fusion Inc
| https://www.php-fusion.co.uk/
+--------------------------------------------------------+
| Filename: Czechia/classes/Templates/Profile.inc
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

/**
 * Class Profile
 *
 * @package CzechiaTheme\Templates
 */
class Profile extends Core {
    public static function DisplayProfile() {
        ?>
        <section class="card">
            {%tab_header%}
            <div class="spacer-sm">
                <div class="clearfix m-b-20">
                    <div class="pull-left">
                        <div class="pull-left m-r-10">{%user_avatar%}</div>
                        <div class="overflow-hide"><h4 class="m-0">{%user_name%}<br/><small>{%user_level%}</small></h4></div>
                    </div>
                    <div class="pull-right m-t-10">{%buttons%}</div>
                </div>

                <div class="clearfix">{%admin_buttons%}</div><hr/>

                <div class="clearfix">{%basic_info%}</div><hr/>

                <div class="clearfix">{%extended_info%}</div>
            </div>
            {%tab_footer%}
        </section>
        <?php
    }

    public static function Field() {
        ?>
        <div id="{%field_id%}" class="row">
            <label class="col-xs-12 col-sm-3"><strong>{%field_title%}</strong></label>
            <div class="col-xs-12 col-sm-9"><span class="profile_text">{%field_value%}</span></div>
        </div>
        <?php
    }

    public static function EditProfile() {
        echo '<div class="card">';
            echo '{%tab_header%}';
                echo '{%open_form%}';
                echo '{%user_name_field%}';
                echo '{%user_email_field%}';
                echo '{%user_hide_email_field%}';
                echo '{%user_reputation_field%}';
                echo '{%user_avatar_field%}';
                echo '{%user_password_field%}';
                echo '{%user_admin_password_field%}';
                echo '{%custom_fields%}';
                echo '{%captcha_fields%}';
                echo '{%eula%}';
                echo '{%post_button%}';
                echo '{%close_form%}';
            echo '{%tab_footer%}';
        echo '</div>';
    }
}
