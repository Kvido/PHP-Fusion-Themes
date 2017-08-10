<?php
/*-------------------------------------------------------+
| PHP-Fusion Content Management System
| Copyright (C) PHP-Fusion Inc
| https://www.php-fusion.co.uk/
+--------------------------------------------------------+
| Filename: Czechia/classes/Footer/News.inc
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
namespace CzechiaTheme\Footer;

require_once INFUSIONS.'news/infusion_db.php';
require_once NEWS_CLASS.'autoloader.php';

use CzechiaTheme\Core;
use \PHPFusion\News\NewsView;

/**
 * Class News
 *
 * @package CzechiaTheme\Footer
 */
class News extends Core {
    public static function Panel() {
        echo '<h3 class="title"><i class="fa fa-bullhorn"></i> '.self::SetLocale('03').'</h3>';
        if (infusion_exists('news')) {

            $data = NewsView::News()->get_NewsItem(['limit' => '0,5', 'order' => 'news_datestamp DESC']);

            if (!empty($data['news_items'])) {
                echo '<ul class="list-style-none">';
                    foreach ($data['news_items'] as $news_id => $news_data) {
                        echo '<li>';
                            echo '<a href="'.$news_data['news_url'].'">'.trim_text($news_data['news_subject'], 40).'</a>';
                            echo '<br/>';
                            echo '<small>';
                                echo '<i class="fa fa-calendar"></i> '.showdate('shortdate', $news_data['news_datestamp']);
                                echo !empty($news_data['news_display_comments']) ? ' · <i class="fa fa-comments-o"></i> '.$news_data['news_display_comments'] : '';
                                echo ' · <i class="fa fa-eye"></i> '.number_format($news_data['news_reads']);
                            echo '</small>';
                        echo '</li>';
                    }
                echo '</ul>';
            } else {
                echo self::SetLocale('04');
            }
        }
    }
}
