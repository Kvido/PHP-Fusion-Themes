<?php
/*-------------------------------------------------------+
| PHP-Fusion Content Management System
| Copyright (C) PHP-Fusion Inc
| https://www.php-fusion.co.uk/
+--------------------------------------------------------+
| Filename: Czechia/classes/Main.inc
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

use \PHPFusion\OutputHandler;
use \PHPFusion\Panels;
use \PHPFusion\SiteLinks;

/**
 * Class Main
 * Main theme class
 *
 * @package CzechiaTheme
 */
class Main extends Core {
    public function __construct() {
        $locale = fusion_get_locale();

        if ($this->GetParam('header') == TRUE) {
            $url = fusion_get_settings('siteurl').'themes/Czechia/assets/';
            OutputHandler::addToFooter('<script type="text/javascript" src="'.$url.'js/scripts.min.js"></script>');
            OutputHandler::addToHead('<link rel="stylesheet" type="text/css" href="'.$url.'scrollbar/jquery.mCustomScrollbar.min.css"/>');
            OutputHandler::addToFooter('<script type="text/javascript" src="'.$url.'scrollbar/jquery.mCustomScrollbar.min.js"></script>');
            OutputHandler::addToJQuery('
                $(".leftmenu .left-content").mCustomScrollbar({
                    theme: "dark-thick",
                    axis: "y",
                    scrollInertia: 500,
                    mouseWheel: {
                        enable: !0,
                        axis: "y",
                        preventDefault: !0
                    },
                    scrollButtons: {enable: true}
                });
            ');

            self::Header();

            $icon = '';
            if (defined('LEFT') && LEFT) {
                $icon = '<a href="#" id="toggle-leftmenu" class="navbar-brand icon"><i class="fa fa-bars"></i></a>';
            }

            $logo = '<a class="navbar-brand hidden-md hidden-lg" href="'.BASEDIR.fusion_get_settings('opening_page').'">'.fusion_get_settings('sitename').'</a>';

            $menu_options = [
                'id'           => 'main-menu',
                'navbar_class' => 'navbar-default',
                'searchbar'    => TRUE,
                'show_header'  => $icon.$logo
            ];

            echo '<div style="min-height: 60px;">';
                echo SiteLinks::setSubLinks($menu_options)->showSubLinks();
            echo '</div>';
        }

        echo '<main id="main-container" class="clearfix">';
            $content = ['sm' => 12, 'md' => 12, 'lg' => 12];
            $right   = ['sm' => 4,  'md' => 3,  'lg' => 3];

            if (defined('RIGHT') && RIGHT && $this->GetParam('right') == TRUE) {
                $content['sm'] = $content['sm'] - $right['sm'];
                $content['md'] = $content['md'] - $right['md'];
                $content['lg'] = $content['lg'] - $right['lg'];
            }

            if (defined('LEFT') && LEFT) {
                echo '<aside class="leftmenu">';
                    echo '<div class="left-content">';
                        echo LEFT;
                    echo '</div>';
                echo '</aside>';
            }

            echo '<div class="container">';

                if ($this->GetParam('notices') == TRUE) {
                    echo renderNotices(getNotices(['all', FUSION_SELF]));
                }

                echo defined('AU_CENTER') && AU_CENTER ? AU_CENTER : '';

                echo '<div class="row m-t-20 m-b-20">';
                    echo '<div class="col-xs-12 col-sm-'.$content['sm'].' col-md-'.$content['md'].' col-lg-'.$content['lg'].'">';
                        echo defined('U_CENTER') && U_CENTER ? U_CENTER : '';
                        echo CONTENT;
                        echo defined('L_CENTER') && L_CENTER ? L_CENTER : '';
                    echo '</div>';

                    if (defined('RIGHT') && RIGHT && $this->GetParam('right') == TRUE) {
                        echo '<div class="col-xs-12 col-sm-'.$right['sm'].' col-md-'.$right['md'].' col-lg-'.$right['lg'].'">';

                        if (defined('RIGHT') && RIGHT) {
                            echo RIGHT;
                        }

                        echo '</div>';
                    }
                echo '</div>';

                if (defined('BL_CENTER') && BL_CENTER) {
                    echo '<div class="row">';
                    echo '<div class="col-xs-12 col-sm-12 col-md-12 col-lg-12">'.BL_CENTER.'</div>';
                    echo '</div>';
                }

            echo '</div>'; // container

        echo '</main>';

        if ($this->GetParam('footer') == TRUE) {
            self::Footer();
        }
    }

    private function Header() {
        $locale = fusion_get_locale();
        $userdata = fusion_get_userdata();
        $languages = fusion_get_enabled_languages();

        echo '<header class="theme-header">';
            echo '<div class="container"><div class="row">';
                echo '<div class="col-xs-12 col-sm-4 col-md-3 col-lg-3">';
                    echo '<a href="'.BASEDIR.fusion_get_settings('opening_page').'" title="'.fusion_get_settings('sitename').'">';
                        echo '<img src="'.BASEDIR.fusion_get_settings('sitebanner').'" class="logo" alt="Logo"/>';
                    echo '</a>';
                echo '</div>';
                echo '<div class="col-xs-12 col-sm-8 col-md-9 col-lg-9">';
                    echo '<div class="navbar-header navbar-right">';
                        echo '<ul class="menu">';

                            if (count($languages) > 1) {
                                echo '<li class="dropdown language-switcher">';
                                    echo '<a href="#" class="dropdown-toggle pointer" data-toggle="dropdown" title="'.LANGUAGE.'">';
                                        echo '<i class="fa fa-globe"></i> ';
                                        echo '<img class="current" style="margin-top: -5px;" src="'.BASEDIR.'locale/'.LANGUAGE.'/'.LANGUAGE.'-s.png" alt="'.translate_lang_names(LANGUAGE).'"/>';
                                        echo '<span class="caret"></span>';
                                    echo '</a>';

                                    echo '<ul class="dropdown-menu">';
                                        foreach ($languages as $language_folder => $language_name) {
                                            echo '<li><a class="display-block" href="'.clean_request('lang='.$language_folder, ['lang'], FALSE).'">';
                                            echo '<img class="m-r-5" src="'.BASEDIR.'locale/'.$language_folder.'/'.$language_folder.'-s.png" alt="'.$language_folder.'"/> ';
                                            echo $language_name;
                                            echo '</a></li>';
                                        }
                                    echo '</ul>';
                                echo '</li>';
                            }

                            if (iMEMBER) {
                                echo '<li class="dropdown">';
                                    echo '<a href="#" class="dropdown-toggle pointer" data-toggle="dropdown">';
                                        echo $userdata['user_name'];
                                        echo display_avatar($userdata, '18px', '', FALSE, 'img-circle m-l-5 link-avatar');
                                        echo ' <span class="caret"></span>';
                                    echo '</a>';

                                    echo '<ul class="dropdown-menu dropdown-user" role="menu">';
                                        echo '<li class="user-information">';
                                            echo '<div class="media">';
                                                $url = BASEDIR.'profile.php?lookup='.$userdata['user_id'];
                                                echo '<a class="pull-left m-r-10" style="width: 60px; height: 60px;" href="'.$url.'">';
                                                echo display_avatar($userdata, '60px', '', FALSE, 'img-circle');
                                                echo '</a>';
                                                echo '<div class="media-body">';
                                                    echo '<h4 class="media-heading">'.$userdata['user_name'].'</h4>';
                                                    echo '<h5 class="m-t-5">'.getuserlevel($userdata['user_level']).'</h5>';
                                                    echo '<h6>'.self::SetLocale('01').': '.$userdata['user_ip'].'</h6>';
                                                echo '</div>';
                                            echo '</div>';
                                        echo '</li>';
                                        echo '<li class="divider"></li>';
                                        echo '<li><a href="'.BASEDIR.'edit_profile.php"><i class="fa fa-pencil fa-fw"></i> '.$locale['UM080'].'</a></li>';
                                        echo '<li class="divider"></li>';
                                        echo '<li><a href="'.BASEDIR.'profile.php?lookup='.$userdata['user_id'].'"><i class="fa fa-eye fa-fw"></i> '.$locale['view'].' '.$locale['profile'].'</a></li>';
                                        echo '<li class="divider"></li>';
                                        echo '<li><a href="'.BASEDIR.'index.php?logout=yes"><i class="fa fa-sign-out fa-fw"></i> <span class="text-danger">'.$locale['logout'].'</span></a></li>';
                                    echo '</ul>';
                                echo '</li>';

                                $msg_count = dbcount(
                                    "('message_id')",
                                    DB_MESSAGES, "message_to=:my_id AND message_read=:unread AND message_folder=:inbox",
                                    [':inbox' => 0, ':my_id' => fusion_get_userdata('user_id'), ':unread' => 0]
                                );

                                $messages_count = '';
                                if ($msg_count > 0) {
                                    $messages_count = '<span class="label label-danger msg-count">'.$msg_count.'</span>';
                                }

                                echo '<li><a href="'.BASEDIR.'messages.php" title="'.$locale['UM081'].'"><i class="fa fa-envelope fa-fw"></i>'.$messages_count.'</a></li>';

                                if (iADMIN) {
                                    echo '<li><a href="'.ADMIN.'index.php'.fusion_get_aidlink().'&pagenum=0" title="'.$locale['global_123'].'"><i class="fa fa-dashboard"></i></a></li>';
                                }
                            } else {
                                echo '<li class="dropdown loginform">';
                                    echo '<a href="#" id="login-register" data-toggle="dropdown"><i class="fa fa-sign-in"></i> '.$locale['login'].' <span class="caret"></span></a>';

                                    echo '<ul class="dropdown-menu" aria-labelledby="login-register">';
                                        echo '<li>'.self::LoginForm().'</li>';
                                        echo '<li>';
                                            echo str_replace(
                                                ['[LINK]', '[/LINK]'],
                                                ['<a href="'.BASEDIR.'lostpassword.php">', '</a>'],
                                                $locale['global_106']
                                            );
                                        echo '</li>';
                                    echo '</ul>';
                                echo '</li>';
                                if (fusion_get_settings('enable_registration')) {
                                    echo '<li><a href="'.BASEDIR.'register.php"><i class="fa fa-user-plus"></i> '.$locale['register'].'</a></li>';
                                }
                            }
                        echo '</ul>';
                    echo '</div>';
                echo '</div>';
            echo '</div></div>';
        echo '</header>';
    }

    private function LoginForm() {
        $locale = fusion_get_locale();

        $action_url = FUSION_SELF.(FUSION_QUERY ? '?'.FUSION_QUERY : '');
        if (isset($_GET['redirect']) && strstr($_GET['redirect'], '/')) {
            $action_url = cleanurl(urldecode($_GET['redirect']));
        }

        echo openform('loginform', 'post', $action_url);
        switch (fusion_get_settings('login_method')) {
            case 2:
                $placeholder = $locale['global_101c'];
                break;
            case 1:
                $placeholder = $locale['global_101b'];
                break;
            default:
                $placeholder = $locale['global_101a'];
        }

        echo form_text('user_name', '', '', ['placeholder' => $placeholder, 'required' => TRUE]);
        echo form_text('user_pass', '', '', ['placeholder' => $locale['global_102'], 'type' => 'password', 'required' => TRUE]);
        echo '<label><input type="checkbox" name="remember_me" value="y"/> '.$locale['global_103'].'</label>';
        echo form_button('login', $locale['global_104'], '', [
            'class' => 'm-t-10 m-b-10 btn-block btn-primary',
            'icon' => 'fa fa-sign-in'
        ]);
        echo closeform();
    }

    private function Footer() {
        echo '<footer class="site-footer">';
            echo '<div id="backtotop" class="center-x"><a href="#" class="button"><i class="fa fa-angle-up"></i></a></div>';

            echo '<div id="footer">';
                echo '<div class="row">';
                    echo defined('USER1') && USER1 ? '<div class="col-xs-12 col-sm-3 col-md-3 col-lg-3">'.USER1.'</div>' : '';
                    echo defined('USER2') && USER2 ? '<div class="col-xs-12 col-sm-3 col-md-3 col-lg-3">'.USER2.'</div>' : '';
                    echo defined('USER3') && USER3 ? '<div class="col-xs-12 col-sm-3 col-md-3 col-lg-3">'.USER3.'</div>' : '';
                    echo defined('USER4') && USER4 ? '<div class="col-xs-12 col-sm-3 col-md-3 col-lg-3">'.USER4.'</div>' : '';
                echo '</div>';

                $grid = 4;
                echo '<div class="row">';
                    echo '<div class="col-xs-12 col-sm-'.$grid.' col-md-'.$grid.' col-lg-'.$grid.'">';
                        echo '<h3 class="title"><i class="fa fa-info-circle"></i> '.$this->SetLocale('02').'</h3>';
                        echo fusion_get_settings('description');
                        echo '<br/>';
                        echo parse_textarea(stripslashes(strip_tags(fusion_get_settings('footer'))));

                        if (fusion_get_settings('visitorcounter_enabled')) {
                            echo '<br/>';
                            echo showcounter();
                        }
                    echo '</div>';

                    echo '<div class="col-xs-12 col-sm-'.$grid.' col-md-'.$grid.' col-lg-'.$grid.'">';
                        Footer\Comments::Panel();
                    echo '</div>';

                    $news = function_exists('infusion_exists') ? infusion_exists('news') : db_exists(DB_PREFIX.'news');
                    if ($news) {
                        echo '<div class="col-xs-12 col-sm-'.$grid.' col-md-'.$grid.' col-lg-'.$grid.'">';
                            Footer\News::Panel();
                        echo '</div>';
                    }
                echo '</div>';
            echo '</div>';

            $errors = showFooterErrors();
            if ($errors) {
                echo '<div class="errors">'.$errors.'</div>';
            }

            $rendertime = fusion_get_settings('rendertime_enabled') == 1 || fusion_get_settings('rendertime_enabled') == 2;

            if ($rendertime) {
                echo '<div id="rendertime">';
                    echo showrendertime();
                    echo showMemoryUsage();
                echo '</div>';
            }

            echo '<div id="copyright" class="clearfix p-b-10">';
                $this->ThemeCopyright();

                echo '<div class="pull-right">';
                    echo showcopyright('', TRUE).showprivacypolicy();
                echo '</div>';
            echo '</div>';
        echo '</footer>';
        echo '<div class="overlay"><!-- --></div>';
    }

    public static function HideAll() {
        Panels::getInstance(TRUE)->hide_panel('RIGHT');
        Panels::getInstance(TRUE)->hide_panel('LEFT');
        Panels::getInstance(TRUE)->hide_panel('AU_CENTER');
        Panels::getInstance(TRUE)->hide_panel('U_CENTER');
        Panels::getInstance(TRUE)->hide_panel('L_CENTER');
        Panels::getInstance(TRUE)->hide_panel('BL_CENTER');
        self::SetParam('header', FALSE);
        self::SetParam('footer', FALSE);
        self::SetParam('notices', FALSE);
    }
}
