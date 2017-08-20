<?php
/*-------------------------------------------------------+
| PHP-Fusion Content Management System
| Copyright (C) PHP-Fusion Inc
| https://www.php-fusion.co.uk/
+--------------------------------------------------------+
| Filename: AdminLTE/classes/AdminPanel.inc
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

use \PHPFusion\Admins;
use \PHPFusion\OutputHandler;

/**
 * Class AdminPanel
 * @package AdminLTE
 */
class AdminPanel extends Components {
    public function __construct() {
        OutputHandler::addToHead('<link rel="stylesheet" href="https://fonts.googleapis.com/css?family=Source+Sans+Pro:300,400,600,700,300italic,400italic,600italic">');
        OutputHandler::addToFooter('<script type="text/javascript" src="'.ADMINLTE.'js/adminlte.min.js"></script>');

        echo '<div class="wrapper">';
            $this->MainHeader();
            $this->MainSidebar();

            echo '<div class="content-wrapper">';
                echo '<div class="notices">';
                    echo renderNotices(getNotices());
                echo '</div>';

                echo CONTENT;
            echo '</div>';

            $this->MainFooter();

            if (!self::IsMobile()) {
                $this->ControlSidebar();
            }

        echo '</div>';
    }

    private function MainHeader() {
        $locale = fusion_get_locale();
        $aidlink = fusion_get_aidlink();
        $sections = Admins::getInstance()->getAdminSections();
        $languages = fusion_get_enabled_languages();

        echo '<header class="main-header">';
            echo '<a href="'.ADMIN.'index.php'.$aidlink.'" class="logo">';
                echo '<span class="logo-mini"><i class="php-fusion"></i></span>';
                echo '<span class="logo-lg">PHP-Fusion</span>';
            echo '</a>';

            echo '<nav class="navbar navbar-static-top">';
                echo '<a href="#" class="sidebar-toggle" data-toggle="push-menu" role="button"><span class="sr-only">Toggle navigation</span></a>';

                echo '<ul class="nav navbar-nav navbar-left hidden-xs">';
                    if (!empty($sections)) {
                        $i = 0;

                        foreach ($sections as $section_name) {
                            $active = (isset($_GET['pagenum']) && $_GET['pagenum'] == $i || !isset($_GET['pagenum']) && Admins::getInstance()->_isActive() == $i) ? ' class="active"' : '';
                            echo '<li'.$active.'><a href="'.ADMIN.'index.php'.$aidlink.'&amp;pagenum='.$i.'" data-toggle="tooltip" data-placement="bottom" title="'.$section_name.'">'.Admins::getInstance()->get_admin_section_icons($i).'</a></li>';
                            $i++;
                        }
                    }
                echo '</ul>';

                echo '<div class="navbar-custom-menu">';
                    echo '<ul class="nav navbar-nav">';
                        if (count($languages) > 1) {
                            echo '<li class="dropdown languages-menu">';
                                echo '<a href="#" class="dropdown-toggle" data-toggle="dropdown">';
                                    echo '<i class="fa fa-globe"></i> <img style="margin-top: -3px;" src="'.BASEDIR.'locale/'.LANGUAGE.'/'.LANGUAGE.'-s.png" alt="'.translate_lang_names(LANGUAGE).'"/>';
                                    echo '<span class="caret"></span>';
                                echo '</a>';
                                echo '<ul class="dropdown-menu">';
                                    foreach ($languages as $language_folder => $language_name) {
                                        echo '<li><a class="display-block" href="'.clean_request('lang='.$language_folder, ['lang'], FALSE).'"><img class="m-r-5" src="'.BASEDIR.'locale/'.$language_folder.'/'.$language_folder.'-s.png" alt="'.$language_folder.'"/> '.$language_name.'</a></li>';
                                    }
                                echo '</ul>';
                            echo '</li>';
                        }

                        $this->MessagesMenu();
                        $this->UserMenu();

                        echo '<li><a href="'.BASEDIR.'index.php"><i class="fa fa-home"></i></a></li>';

                        if (!self::IsMobile()) {
                            echo '<li><a href="#" data-toggle="control-sidebar"><i class="fa fa-gears"></i></a></li>';
                        }
                    echo '</ul>';
                echo '</div>';
            echo '</nav>';
        echo '</header>';
    }

    private function MessagesMenu() {
        $locale = fusion_get_locale();
        $messages = self::Messages();
        $msg_icon = !empty($messages) ? '<span class="label label-danger" style="margin-top: inherit;">'.count($messages).'</span>' : '';

        echo '<li class="dropdown messages-menu">';
            echo '<a href="'.BASEDIR.'messages.php" class="dropdown-toggle" data-toggle="dropdown">';
                echo '<i class="fa fa-envelope-o"></i>'.$msg_icon;
                echo '<span class="caret"></span>';
            echo '</a>';
            echo '<ul class="dropdown-menu">';
                echo '<li class="header text-center">'.$this->SetLocale('001').' '.format_word(count($messages), $locale['fmt_message']).'</li>';
                echo '<li><ul class="menu">';
                    if (!empty($messages)) {
                        foreach ($messages as $message) {
                            echo '<li>';
                                echo '<a href="'.BASEDIR.'messages.php?folder=inbox&amp;msg_read='.$message['link'].'">';
                                    echo '<div class="pull-left">';
                                        echo display_avatar($message['user'], '40px', '', FALSE, 'img-circle');
                                    echo '</div>';
                                    echo '<h4>';
                                        echo $message['user']['user_name'];
                                        echo '<small><i class="fa fa-clock-o"></i> '.$message['datestamp'].'</small>';
                                    echo '</h4>';
                                    echo '<p>'.trim_text($message['title'], 20).'</p>';
                                echo '</a>';
                            echo '</li>';
                        }
                    } else {
                        echo '<li class="text-center">'.$this->SetLocale('002').'</li>';
                    }

                echo '</ul></li>';
                echo '<li class="footer"><a href="'.BASEDIR.'messages.php?msg_send=new" class="text-bold">'.$this->SetLocale('003').'</a></li>';
            echo '</ul>';
        echo '</li>';
    }

    private function UserMenu() {
        $locale = fusion_get_locale();
        $userdata = fusion_get_userdata();

        echo '<li class="dropdown user user-menu">';
            echo '<a href="#" class="dropdown-toggle" data-toggle="dropdown">';
                echo display_avatar($userdata, '25px', '', FALSE, 'user-image');
                echo '<span class="hidden-xs">'.$userdata['user_name'].'</span>';
                echo '<span class="caret"></span>';
            echo '</a>';
            echo '<ul class="dropdown-menu">';
                echo '<li class="user-header">';
                    echo display_avatar($userdata, '90px', '', FALSE, 'img-circle');
                    echo '<p>'.$userdata['user_name'].'<small>'.$this->SetLocale('004').' '.showdate('longdate', $userdata['user_joined']).'</small></p>';
                echo '</li>';
                echo '<li class="user-body">';
                    echo '<div class="row">';
                        echo '<div class="col-xs-6 text-center">';
                            echo '<a href="'.BASEDIR.'edit_profile.php"><i class="fa fa-pencil fa-fw"></i> '.$locale['UM080'].'</a>';
                        echo '</div>';
                        echo '<div class="col-xs-6 text-center">';
                            echo '<a href="'.BASEDIR.'profile.php?lookup='.$userdata['user_id'].'"><i class="fa fa-eye fa-fw"></i> '.$locale['view'].' '.$locale['profile'].'</a>';
                        echo '</div>';
                    echo '</div>';
                echo '</li>';
                echo '<li class="user-footer">';
                    echo '<div class="pull-left">';
                        echo '<a href="'.FUSION_REQUEST.'&amp;logout" class="btn btn-default btn-flat">'.$locale['admin-logout'].'</a>';
                    echo '</div>';
                    echo '<div class="pull-right">';
                        echo '<a href="'.BASEDIR.'index.php?logout=yes" class="btn btn-default btn-flat">'.$locale['logout'].'</a>';
                    echo '</div>';
                echo '</li>';
            echo '</ul>';
        echo '</li>';
    }

    private function MainSidebar() {
        $locale = fusion_get_locale();
        $userdata = fusion_get_userdata();
        $useronline = $userdata['user_lastvisit'] >= time() - 900 ? TRUE : FALSE;

        $this->SearchAjax();

        echo '<aside class="main-sidebar">';
            echo '<section class="sidebar">';
                echo '<div class="user-panel">';
                    echo '<div class="pull-left image">';
                        echo display_avatar($userdata, '45px', '', FALSE, 'img-circle');
                    echo '</div>';
                    echo '<div class="pull-left info">';
                        echo '<p>'.$userdata['user_name'].'</p>';
                        echo '<a href="#">';
                            echo '<i class="fa fa-circle '.($useronline ? 'text-success' : 'text-danger').'"></i> ';
                            echo $useronline ? $locale['online'] : $locale['offline'];
                        echo '</a>';
                    echo '</div>';
                echo '</div>';

                echo '<div class="sidebar-form">';
                    echo '<input type="text" id="search_pages" name="search_pages" class="form-control" placeholder="'.$this->SetLocale('005').'">';
                echo '</div>';
                echo '<ul class="sidebar-menu" id="search_result" style="display: none;"></ul>';
                echo '<img id="ajax-loader" style="width: 30px; display: none;" class="img-responsive center-x m-t-10" alt="Ajax Loader" src="'.ADMINLTE.'images/loader.svg"/>';

                $this->SidebarMenu();

            echo '</section>';
        echo '</aside>';
    }

    private function SearchAjax() {
        OutputHandler::addToJQuery('$("#search_pages").bind("keyup", function (e) {
            var data = {
                "pagestring": $(this).val(),
                "url": "'.$_SERVER['REQUEST_URI'].'",
            };

            $.ajax({
                url: "'.ADMINLTE.'acp_search.php'.fusion_get_aidlink().'",
                method: "get",
                data: $.param(data),
                beforeSend: function () {
                    $("#ajax-loader").show();
                },
                success: function (e) {
                    if ($("#search_pages").val() == "") {
                        $("#adl").show();
                        $("#search_result").html(e).hide();
                        $("#search_result li").html(e).hide();
                    } else {
                        $("#search_result").html(e).show();
                        $("#adl").hide();
                    }
                },
                complete: function () {
                    $("#ajax-loader").hide();
                }
            });
        });');
    }

    private function SidebarMenu() {
        $locale = fusion_get_locale();
        $aidlink = fusion_get_aidlink();
        $admin_sections = Admins::getInstance()->getAdminSections();
        $admin_pages = Admins::getInstance()->getAdminPages();

        echo '<ul id="adl" class="sidebar-menu" data-widget="tree">';
            foreach ($admin_sections as $i => $section_name) {
                $active = ((isset($_GET['pagenum']) && $_GET['pagenum'] == $i) || (!isset($_GET['pagenum']) && Admins::getInstance()->_isActive() == $i)) ? TRUE : FALSE;

                if (!empty($admin_pages[$i]) && is_array($admin_pages[$i])) {
                    echo '<li class="treeview'.($active ? ' active' : '').'">';
                        echo '<a href="#">';
                            echo Admins::getInstance()->get_admin_section_icons($i).' <span>'.$section_name.'</span>';
                            echo '<span class="pull-right-container">';
                                echo '<i class="fa fa-angle-left pull-right"></i>';
                                echo ($i > 4 ? '<small class="label pull-right bg-blue">'.count($admin_pages[$i]).'</small>' : '');
                            echo '</span>';
                        echo '</a>';
                        echo '<ul class="treeview-menu">';
                            foreach ($admin_pages[$i] as $key => $data) {
                                if (checkrights($data['admin_rights'])) {
                                    $sub_active = $data['admin_link'] == Admins::getInstance()->_currentPage() ? TRUE : FALSE;

                                    $title = $data['admin_title'];
                                    if ($data['admin_page'] !== 5) {
                                        $title = isset($locale[$data['admin_rights']]) ? $locale[$data['admin_rights']] : $title;
                                    }

                                    $icon = '<img class="m-r-5" src="'.get_image('ac_'.$data['admin_rights']).'" alt="'.$title.'"/>';

                                    echo '<li'.($sub_active ? ' class="active"' : '').'>';
                                        echo '<a href="'.ADMIN.$data['admin_link'].$aidlink.'">'.$icon.' '.$title.'</a>';
                                    echo '</li>';
                                }
                            }
                        echo '</ul>';
                    echo '</li>';
                } else {
                    echo '<li'.($active ? ' class="active"' : '').'><a href="'.ADMIN.'index.php'.$aidlink.'&amp;pagenum=0">';
                        echo Admins::getInstance()->get_admin_section_icons($i).' <span>'.$section_name.'</span>';
                    echo '</a></li>';
                }
            }
        echo '</ul>';
    }

    private function MainFooter() {
        $locale = fusion_get_locale();

        echo '<footer class="main-footer">';
            echo showFooterErrors();

            if (fusion_get_settings('rendertime_enabled')) {
                echo showrendertime().showMemoryUsage().'<br />';
            }

            echo '<strong>';
                echo 'AdminLTE Admin Theme &copy; '.date('Y').' '.$this->SetLocale('006').' <a href="https://github.com/RobiNN1" target="_blank">RobiNN</a> ';
                echo $locale['and'].' <a href="https://adminlte.io" target="_blank">Almsaeed Studio</a>';
            echo '</strong>';
            echo '<br/>'.str_replace('<br />', ' | ', showcopyright());
        echo '</footer>';
    }

    private function ControlSidebar() {
        OutputHandler::addToFooter('<script type="text/javascript" src="'.ADMINLTE.'js/control-sidebar.min.js"></script>');

        echo '<aside class="control-sidebar control-sidebar-dark">';
            echo '<div class="content">';
                echo '<h4 class="control-sidebar-heading">'.$this->SetLocale('008').'</h4>';

                echo '<div class="form-group">';
                    echo '<label class="control-sidebar-subheading">';
                        echo '<input type="checkbox" data-layout="fixed" class="pull-right"> '.$this->SetLocale('009');
                    echo '</label>';
                echo '</div>';

                echo '<div class="form-group">';
                    echo '<label class="control-sidebar-subheading">';
                        echo '<input type="checkbox" data-layout="sidebar-collapse" class="pull-right"> '.$this->SetLocale('010');
                    echo '</label>';
                echo '</div>';

                echo '<h4 class="control-sidebar-heading">'.$this->SetLocale('011').'</h4>';
                echo '<h5>'.$this->SetLocale('012').'</h5>';

                echo '<ul class="list-unstyled clearfix">';
                    echo '<li class="skin-preview">';
                        echo '<a href="javascript:void(0)" data-skin="skin-blue" class="clearfix full-opacity-hover skin">';
                            echo '<div><span class="header-left" style="background: #367fa9"></span><span class="bg-light-blue header-right"></span></div>';
                            echo '<div><span class="body-left" style="background: #222d32"></span><span class="body-right" style="background: #f4f5f7"></span></div>';
                        echo '</a>';
                    echo '</li>';
                    echo '<li class="skin-preview">';
                        echo '<a href="javascript:void(0)" data-skin="skin-black" class="clearfix full-opacity-hover skin">';
                            echo '<div style="box-shadow: 0 0 2px rgba(0,0,0,0.1)" class="clearfix"><span class="header-left" style="background: #fefefe"></span><span class="header-right" style="background: #fefefe"></span></div>';
                            echo '<div><span class="body-left" style="background: #222"></span><span class="body-right" style="background: #f4f5f7"></span></div>';
                        echo '</a>';
                    echo '</li>';
                    echo '<li class="skin-preview">';
                        echo '<a href="javascript:void(0)" data-skin="skin-purple" class="clearfix full-opacity-hover skin">';
                            echo '<div><span class="header-left bg-purple-active"></span><span class="bg-purple header-right"></span></div>';
                            echo '<div><span class="body-left" style="background: #222d32"></span><span class="body-right" style="background: #f4f5f7"></span></div>';
                        echo '</a>';
                    echo '</li>';
                    echo '<li class="skin-preview">';
                        echo '<a href="javascript:void(0)" data-skin="skin-green" class="clearfix full-opacity-hover skin">';
                            echo '<div><span class="header-left bg-green-active"></span><span class="bg-green header-right"></span></div>';
                            echo '<div><span class="body-left" style="background: #222d32"></span><span class="body-right" style="background: #f4f5f7"></span></div>';
                        echo '</a>';
                    echo '</li>';
                    echo '<li class="skin-preview">';
                        echo '<a href="javascript:void(0)" data-skin="skin-red" class="clearfix full-opacity-hover skin">';
                            echo '<div><span class="header-left bg-red-active"></span><span class="bg-red header-right"></span></div>';
                            echo '<div><span class="body-left" style="background: #222d32"></span><span class="body-right" style="background: #f4f5f7"></span></div>';
                        echo '</a>';
                    echo '</li>';
                    echo '<li class="skin-preview">';
                        echo '<a href="javascript:void(0)" data-skin="skin-yellow" class="clearfix full-opacity-hover skin">';
                            echo '<div><span class="header-left bg-yellow-active"></span><span class="bg-yellow header-right"></span></div>';
                            echo '<div><span class="body-left" style="background: #222d32"></span><span class="body-right" style="background: #f4f5f7"></span></div>';
                        echo '</a>';
                    echo '</li>';
                echo '</ul>';

                echo '<h5>'.$this->SetLocale('013').'</h5>';

                echo '<ul class="list-unstyled clearfix">';
                    echo '<li class="skin-preview">';
                        echo '<a href="javascript:void(0)" data-skin="skin-blue-light" class="clearfix full-opacity-hover skin">';
                            echo '<div><span class="header-left" style="background: #367fa9"></span><span class="bg-light-blue header-right"></span></div>';
                            echo '<div><span class="body-left" style="background: #f9fafc"></span><span class="body-right" style="background: #f4f5f7"></span></div>';
                        echo '</a>';
                    echo '</li>';
                    echo '<li class="skin-preview">';
                        echo '<a href="javascript:void(0)" data-skin="skin-black-light" class="clearfix full-opacity-hover skin">';
                            echo '<div style="box-shadow: 0 0 2px rgba(0,0,0,0.1)" class="clearfix"><span class="header-left" style="background: #fefefe"></span><span class="header-right" style="background: #fefefe"></span></div>';
                            echo '<div><span class="body-left" style="background: #f9fafc"></span><span class="body-right" style="background: #f4f5f7"></span></div>';
                        echo '</a>';
                    echo '</li>';
                    echo '<li class="skin-preview">';
                        echo '<a href="javascript:void(0)" data-skin="skin-purple-light" class="clearfix full-opacity-hover skin">';
                            echo '<div><span class="header-left bg-purple-active"></span><span class="bg-purple header-right"></span></div>';
                            echo '<div><span class="body-left" style="background: #f9fafc"></span><span class="body-right" style="background: #f4f5f7"></span></div>';
                        echo '</a>';
                    echo '</li>';
                    echo '<li class="skin-preview">';
                        echo '<a href="javascript:void(0)" data-skin="skin-green-light" class="clearfix full-opacity-hover skin">';
                            echo '<div><span class="header-left bg-green-active"></span><span class="bg-green header-right"></span></div>';
                            echo '<div><span class="body-left" style="background: #f9fafc"></span><span class="body-right" style="background: #f4f5f7"></span></div>';
                        echo '</a>';
                    echo '</li>';
                    echo '<li class="skin-preview">';
                        echo '<a href="javascript:void(0)" data-skin="skin-red-light" class="clearfix full-opacity-hover skin">';
                            echo '<div><span class="header-left bg-red-active"></span><span class="bg-red header-right"></span></div>';
                            echo '<div><span class="body-left" style="background: #f9fafc"></span><span class="body-right" style="background: #f4f5f7"></span></div>';
                        echo '</a>';
                    echo '</li>';
                    echo '<li class="skin-preview">';
                        echo '<a href="javascript:void(0)" data-skin="skin-yellow-light" class="clearfix full-opacity-hover skin">';
                            echo '<div><span class="header-left bg-yellow-active"></span><span class="bg-yellow header-right"></span></div>';
                            echo '<div><span class="body-left" style="background: #f9fafc"></span><span class="body-right" style="background: #f4f5f7"></span></div>';
                        echo '</a>';
                    echo '</li>';
                echo '</ul>';

            echo '</div>';
        echo '</aside>';

        echo '<div class="control-sidebar-bg"></div>';
    }
}
