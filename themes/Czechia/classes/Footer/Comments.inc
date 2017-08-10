<?php
/*-------------------------------------------------------+
| PHP-Fusion Content Management System
| Copyright (C) PHP-Fusion Inc
| https://www.php-fusion.co.uk/
+--------------------------------------------------------+
| Filename: Czechia/classes/Footer/Comments.inc
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

use CzechiaTheme\Core;

/**
 * Class Comments
 *
 * @package CzechiaTheme\Footer
 */
class Comments extends Core {
    public static function Panel() {
        $locale = fusion_get_locale();

        echo '<h3 class="title"><i class="fa fa-comments-o"></i> '.self::SetLocale('13').'</h3>';

        $displayComments = 5;
        $comments_per_page = fusion_get_settings('comments_per_page');

        $result = dbquery("SELECT tc.comment_id, tc.comment_item_id, tc.comment_type, tc.comment_message, tu.user_id, tu.user_name, tu.user_status, tu.user_avatar
            FROM ".DB_COMMENTS." tc
            LEFT JOIN ".DB_USERS." tu ON tu.user_id = tc.comment_name
            WHERE tc.comment_hidden='0'
            ORDER BY tc.comment_datestamp DESC
        ");

        if (dbrows($result)) {
            $i = 0;

            $info = [];

            while ($data = dbarray($result)) {
                if ($i == $displayComments) {
                    break;
                }

                switch ($data['comment_type']) {
                    case 'A':
                        $results = dbquery("SELECT ar.article_subject
                            FROM ".DB_ARTICLES." as ar
                            INNER JOIN ".DB_ARTICLE_CATS." as ac ON ac.article_cat_id = ar.article_cat
                            WHERE ar.article_id='".$data['comment_item_id']."' AND ar.article_draft='0'
                            AND ".groupaccess('ar.article_visibility')."
                            ".(multilang_table('AR') ? " AND ar.article_language='".LANGUAGE."'" : '')."
                            ORDER BY ar.article_datestamp DESC
                        ");

                        if (dbrows($results)) {
                            $article_data = dbarray($results);
                            $commentStart = dbcount("(comment_id)", DB_COMMENTS, "comment_item_id='".$data['comment_item_id']."' AND comment_type='A' AND comment_id<=".$data['comment_id']);
                            $commentStart = $commentStart > $comments_per_page ? "&amp;c_start_news_comments=".((floor($commentStart / $comments_per_page) * $comments_per_page) - $comments_per_page) : '';

                            $item = [
                                'avatar'  => display_avatar($data, '35px', '', TRUE, 'img-circle m-r-10 m-t-5'),
                                'title'   => $article_data['article_subject'],
                                'c_url'   => INFUSIONS.'articles/articles.php?article_id='.$data['comment_item_id'].$commentStart.'#c'.$data['comment_id'],
                                'c_title' => $data['comment_message']
                            ];

                            $info[] = $item;
                        }
                        continue;
                    case 'B':
                        $results = dbquery("SELECT d.blog_subject
                            FROM ".DB_BLOG." as d
                            INNER JOIN ".DB_BLOG_CATS." as c ON c.blog_cat_id=d.blog_cat
                            WHERE d.blog_id='".$data['comment_item_id']."' AND ".groupaccess('d.blog_visibility')."
                            ".(multilang_table('BL') ? " AND d.blog_language='".LANGUAGE."'" : '')."
                            ORDER BY d.blog_datestamp DESC
                        ");

                        if (dbrows($results)) {
                            $blog_data = dbarray($results);
                            $commentStart = dbcount("(comment_id)", DB_COMMENTS, "comment_item_id='".$data['comment_item_id']."' AND comment_type='B' AND comment_id<=".$data['comment_id']);
                            $commentStart = $commentStart > $comments_per_page ? "&amp;c_start_news_comments=".((floor($commentStart / $comments_per_page) * $comments_per_page) - $comments_per_page) : '';

                            $item = [
                                'avatar'  => display_avatar($data, '35px', '', TRUE, 'img-circle m-r-10 m-t-5'),
                                'title'   => $blog_data['blog_subject'],
                                'c_url'   => INFUSIONS.'blog/blog.php?readmore='.$data['comment_item_id'].$commentStart.'#c'.$data['comment_id'],
                                'c_title' => $data['comment_message']
                            ];

                            $info[] = $item;
                        }
                        continue;
                    case 'N':
                        $results = dbquery("SELECT ns.news_subject
                            FROM ".DB_NEWS." as ns
                            LEFT JOIN ".DB_NEWS_CATS." as nc ON nc.news_cat_id = ns.news_cat
                            WHERE ns.news_id='".$data['comment_item_id']."' AND (ns.news_start='0' OR ns.news_start<='".TIME."')
                            AND (ns.news_end='0' OR ns.news_end>='".TIME."') AND ns.news_draft='0'
                            AND ".groupaccess('ns.news_visibility')."
                            ".(multilang_table('NS') ? "AND ns.news_language='".LANGUAGE."'" : '')."
                            ORDER BY ns.news_datestamp DESC
                        ");

                        if (dbrows($results)) {
                            $news_data = dbarray($results);
                            $commentStart = dbcount("(comment_id)", DB_COMMENTS, "comment_item_id='".$data['comment_item_id']."' AND comment_type='N' AND comment_id<=".$data['comment_id']);
                            $commentStart = $commentStart > $comments_per_page ? "&amp;c_start_news_comments=".((floor($commentStart / $comments_per_page) * $comments_per_page) - $comments_per_page) : '';

                            $item = [
                                'avatar'  => display_avatar($data, '35px', '', TRUE, 'img-circle m-r-10 m-t-5'),
                                'title'   => $news_data['news_subject'],
                                'c_url'   => INFUSIONS.'news/news.php?readmore='.$data['comment_item_id'].$commentStart.'#c'.$data['comment_id'],
                                'c_title' => $data['comment_message']
                            ];

                            $info[] = $item;
                        }
                        continue;
                    case 'P':
                        $results = dbquery("SELECT p.photo_title
                            FROM ".DB_PHOTOS." as p
                            INNER JOIN ".DB_PHOTO_ALBUMS." as a ON p.album_id=a.album_id
                            WHERE p.photo_id='".$data['comment_item_id']."' AND ".groupaccess('a.album_access')."
                            ".(multilang_table('PG') ? " AND a.album_language='".LANGUAGE."'" : '')."
                            ORDER BY p.photo_datestamp DESC
                        ");

                        if (dbrows($results)) {
                            $photo_data = dbarray($results);
                            $commentStart = dbcount("(comment_id)", DB_COMMENTS, "comment_item_id='" . $data['comment_item_id'] . "' AND comment_type='P' AND comment_id<=" . $data['comment_id']);
                            $commentStart = $commentStart > $comments_per_page ? "&amp;c_start_news_comments=" . ((floor($commentStart / $comments_per_page) * $comments_per_page) - $comments_per_page) : '';

                            $item = [
                                'avatar'  => display_avatar($data, '35px', '', TRUE, 'img-circle m-r-10 m-t-5'),
                                'title'   => $photo_data['photo_title'],
                                'c_url'   => INFUSIONS.'gallery/gallery.php?photo_id='.$data['comment_item_id'].$commentStart.'#c'.$data['comment_id'],
                                'c_title' => $data['comment_message']
                            ];

                            $info[] = $item;
                        }
                        continue;
                    case 'D':
                        $results = dbquery("SELECT
                            d.download_title
                            FROM ".DB_DOWNLOADS." as d
                            INNER JOIN ".DB_DOWNLOAD_CATS." as c ON c.download_cat_id=d.download_cat
                            WHERE d.download_id='".$data['comment_item_id']."' AND ".groupaccess('d.download_visibility')."
                            ".(multilang_table("DL") ? " AND c.download_cat_language='".LANGUAGE."'" : '')."
                            ORDER BY d.download_datestamp DESC
                        ");

                        if (dbrows($results)) {
                            $download_data = dbarray($results);
                            $commentStart = dbcount("(comment_id)", DB_COMMENTS, "comment_item_id='".$data['comment_item_id']."' AND comment_type='D' AND comment_id<=".$data['comment_id']);
                            $commentStart = $commentStart > $comments_per_page ? "&amp;c_start_news_comments=".((floor($commentStart / $comments_per_page) * $comments_per_page) - $comments_per_page) : "";

                            $item = [
                                'avatar'  => display_avatar($data, '35px', '', TRUE, 'img-circle m-r-10 m-t-5'),
                                'title'   => $download_data['download_title'],
                                'c_url'   => INFUSIONS.'downloads/downloads.php?download_id='.$data['comment_item_id'].$commentStart.'#c'.$data['comment_id'],
                                'c_title' => $data['comment_message']
                            ];

                            $info[] = $item;
                        }
                        break;
                }

                $i++;
            }

            echo '<ul class="list-style-none">';
                foreach ($info as $id => $data) {
                    echo '<li id="comment-'.$id.'" class="m-t-5">';
                        echo '<div class="pull-left">'.$data['avatar'].'</div>';
                        echo '<strong>'.trim_text($data['title'], 40).'</strong>';
                        echo '<div class="clearfix"><a href="'.$data['c_url'].'">'.trim_text($data['c_title'], 35).'</a></div>';
                    echo '</li>';
                }
            echo '</ul>';

        } else {
            echo $locale['global_026'];
        }
    }
}
