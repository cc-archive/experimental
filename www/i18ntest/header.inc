<?php
/* 
 * This is a driver for the class CCLanguage in cc-language.inc
 *
 * This file is used here in accordance with the GNU GPL which is copied in the 
 * COPYING file accompanying this file.
 *
 * Copyright 2006, Creative Commons.
 * Copyright 2006, Jon Phillips.
 *
 */

// contains CCLanguage and some defines
include('cc-language.php');



function print_var (&$var)
{
    echo "<pre>";
    print_r( $var );
    echo "</pre>";
}

function print_message (&$message)
{
    echo "<p>$message</p>\n";
}


/* START OF DOCUMENT */

session_start();

// This nastiness handles session storage 
$ccLang = &$_SESSION['lang'];

if ( ! isset($ccLang) || isset($_REQUEST['update'] ) ) {
    $ccLang = new CCLanguage(&$_REQUEST['lang']);
    if (DEBUG) echo "<p>created new object</p>";
}
else 
{
    if ( isset($_REQUEST['lang']) ) {
        $ccLang->SetLanguage(&$_REQUEST['lang']);
        if (DEBUG) echo "<p>set new language</p>";
    }

    if ( isset($_REQUEST['localepref']) ) {
        $ccLang->SetLocalePref(&$_REQUEST['localepref']);
        if (DEBUG) echo "<p>set new locale pref</p>";
    }

    if (DEBUG) echo "<p>Using session language</p>";
}

// $ccLang->DebugLanguages();

$ccLang->Init();

// START OF REAL CONTENT

echo "<h3>FILENAME: " . $_SERVER['PHP_SELF'] . "</h3>\n";
?>

<h4>Special Tricks</h4>

<ul>
<li><a href="?update=1">update</a> (reinstantiate objects for sessions)</li>
</ul>

<h4>Select Locale Preference</h4>

<?php
echo "Current Locale Preference: <b>" . $ccLang->GetLocalePref() . "</b>\n";
echo "<ul>\n";

foreach ( $ccLang->GetPossibleLocalePrefs() as $key => $value )
{
    echo "<li><a href=\"?localepref=$key\">$key</a></li>\n";
}
?>
</ul>

<h4>Select Language</h4>

<?php
echo "Current Language: <b>" . $ccLang->GetLanguage() . "</b>\n";
echo "<ul>\n";

foreach ( $ccLang->GetPossibleLanguages() as $lang => $value )
{
    echo "<li><a href=\"?lang=$lang\">$lang</a></li>\n";
}
?>
</ul>


