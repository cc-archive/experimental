<?php
// Simple language tests for i18n with php

//$languages = array('en' => array('English','English'), 
//                   'zh_CN' => array('China-Mainland', 'China-Mainland'));
$languages = array('en_EN', 'de_DE', 'zh_CN');

define('DEFAULT_LANG', 'en');
define('DEBUG', true);

// if (DEBUG)
//    echo "<p>" . $_REQUEST['lang'] . "</p>\n";

if ($_REQUEST['lang'] && in_array($_REQUEST['lang'],$languages))
    $language = &$_REQUEST['lang'];
else
    $language = DEFAULT_LANG;

// $language = 'en';
putenv("LANG=$language"); 
setlocale(LC_ALL, $language);

// Set the text domain as 'messages'
$domain = 'messages';
bindtextdomain($domain, "./locale"); 
textdomain($domain);
?>

<h4>Select Language</h4>

<ul>
<?php
echo "Current Language: <b>$language</b>\n";

foreach ($languages as $lang)
{
    echo "<li><a href=\"?lang=$lang\">$lang</a></li>\n";
}
?>
</ul>

<?php 
    echo "<h3>" . $_SERVER['PHP_SELF'] . "</h3>\n";
?>
