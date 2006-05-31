<?php
// Simple language tests for i18n with php

//$languages = array('en' => array('English','English'), 
//                   'zh_CN' => array('China-Mainland', 'China-Mainland'));

# $languages = array('en_EN', 'de_DE', 'zh_CN');

define('DEFAULT_LANG', 'en');
define('DEBUG', true);
define('DEFAULT_LOCALE', 'locale');
define('DEFAULT_LOCALE_PREF', DEFAULT_LOCALE . '/default');

define('PROJECT_NAME', 'testsite.org');

// global array for languages
$languages = array();


// TODO: Come up with a sensible way to track current default locale pref and 
// current language


function load_languages ($locale_dir = DEFAULT_LOCALE, 
                         $catalog_fn = "messages.mo") 
{
    global $languages;
    
    // read in each locale preference folder
    $locale_dirs = glob( $locale_dir . '/*', GLOB_ONLYDIR ); 

    if ( count($locale_dirs) == 0 )
        return false;

    foreach ( $locale_dirs as $dir ) {
	// Read in each folder (language) for consideration
        $lang_dirs = glob( "$dir/*", GLOB_ONLYDIR );
	// if the locale pref. folder has no languages, then don't load it
	if ( count($lang_dirs) == 0 )
	    continue;
	$locale_pref = basename($dir);
	$languages['locale'][$locale_pref] = array('path' => $dir);

	foreach ( $lang_dirs as $lang_dir ) {
	    $lang_name = basename($lang_dir);
	    // if there is no readable mo file, then get the hell out
            if ( is_readable( "$lang_dir/LC_MESSAGES/$catalog_fn" ) ) {
		$languages['locale'][$locale_pref]['language'][$lang_name] = 
		    array('path' => $lang_dir); 
	    }
	}
    }
    // TODO: Need one more check here of the array and if there is nothing
    // usable, then should return a false here and remove that bad shit from
    // the global array.

    return true;
}

/**
 *
 * This is where one should set the default locale and language upon startup
 * of the app.
 */
function set_locale_pref ($locale_pref = DEFAULT_LOCALE)
{
    global $languages;
    
    $locale_setting = &$languages['setting']['locale'];

    // conditions for not attempting anything
    if ( $locale_pref == $locale_setting )
        return true;

    $locale_tests = array(&$locale_pref, 
                          &$_SERVER['HTTP_HOST'], 
			  PROJECT_NAME);

    foreach ( $locale_tests as $test )
    {
        if ( defined($languages['locale'][$test]) ) {
	        $locale_setting = $test;
	        return true;
        }
    }

    /*
    if ( defined($languages['locale'][$locale_pref]) ) {
	    $locale_setting = $locale_pref;
	    return true;
    }

    // try to set it to something default
    if ( defined($languages['locale'][$_SERVER['HTTP_HOST']]) ) {
	    $locale_setting = $_SERVER['HTTP_HOST'];
	    return true;
    }

    if ( defined($languages['locale'][PROJECT_NAME]) ) {
	    $locale_setting = PROJECT_NAME;
	    return true;
    }
    */

    // if all else fails, then just set it to normal
    $locale_setting = DEFAULT_LOCALE;
    return false;
}

// TODO: finish fixing this, testing and getting it to work with the foreach 
// loop

function set_language ($lang_pref = DEFAULT_LANG)
{
    global $languages;

    $lang_setting = &$languages['setting']['language'];
    $locale_setting = &$languages['setting']['locale'];
    $lang_possible = &$languages['locale'][$locale_setting]['language'];

    if ( $lang_pref == $lang_setting )
        return true;

    $lang_tests = array(&$lang_pref, 
                        $lang_code . "_" . strtoupper($lang_pref));

    foreach ( $lang_tests as $test )
    {
        if ( defined($lang_possible[$test]) ) {
	        $lang_setting = $lang_possible[$test];
	        return true;
        }
    }


    /*if ( defined($lang_possible[$lang_code]) )
    {
        $lang_setting = $lang_possible[$lang_code];
	return true;
    }
    else if ( 2 == strlen($lang_code) && 
        defined($lang_possible[$lang_code . "_" . strtoupper($lang_code)]) )
    {
        $lang_setting = 
	    $lang_possible[$lang_code . "_". strtoupper($lang_code)];
        return true;
    }*/

    // if all else fails set it to the default
    $lang_setting = DEFAULT_LANG;
    return false;
}

function debug_languages ()
{
    global $languages;

    echo "<pre>";
    print_r( $languages );
    echo "</pre>";
}

load_languages();
set_locale_pref();
// set_language();
debug_languages();
exit;


if ($_REQUEST['lang'] && in_array($_REQUEST['lang'],$languages))
    $language = &$_REQUEST['lang'];
else
    $language = DEFAULT_LANG;

// $language = 'en';
putenv("LANG=$language"); 
setlocale(LC_ALL, $language);

// Set the text domain as 'messages'
$domain = 'messages';
bindtextdomain($domain, $locale_dir); 
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
