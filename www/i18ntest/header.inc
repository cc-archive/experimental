<?php
// Simple language tests for i18n with php
  
    
// default language is general english and not en_US
define('DEFAULT_LANG', '');
define('DEBUG', true);
define('DEFAULT_LOCALE', 'locale');
define('DEFAULT_LOCALE_PREF', 'default');
define('DEFAULT_LOCALE_PREF_DIR', DEFAULT_LOCALE . '/' . DEFAULT_LOCALE_PREF);
define('DEFAULT_LOCALE_DOMAIN', 'messages');

define('PROJECT_NAME', 'testsite.org');
    

session_start();

    
// TODO: Come up with a sensible way to track current default locale pref and 
// current language
    
    
class CCLanguage 
{
    var $_all_languages;
   
    var $_language;
    
    var $_locale_pref;
    
    var $_domain;
    
    function CCLanguage ( $language = '',
                          $locale_dir = DEFAULT_LOCALE, 
                          $locale     = DEFAULT_LOCALE_PREF,
			  $domain     = DEFAULT_LOCALE_DOMAIN )
    {
	$this->_all_languages = array();
	$this->_domain = $domain;
	
        $this->loadLanguages( $locale_dir );
	$this->setLocalePref( $locale );
	$this->setLanguage( $language );
    }
   
    function loadLanguages ($locale_dir = DEFAULT_LOCALE, 
                            $catalog_fn = "messages.mo") 
    {
	// try to head off any type of malicious search
	if ( empty($locale_dir) || $locale_dir == '/' )
	    return false;

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
        $this->_all_languages['locale'][$locale_pref] = array('path' => $dir);
    
        foreach ( $lang_dirs as $lang_dir ) {
            $lang_name = basename($lang_dir);
            // if there is no readable mo file, then get the hell out
                if ( is_readable( "$lang_dir/LC_MESSAGES/$catalog_fn" ) ) {
            $this->_all_languages['locale'][$locale_pref]['language'][$lang_name] = 
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
    function setLocalePref ($locale_pref = DEFAULT_LOCALE_PREF)
    {
        // $locale_setting = &$this->_all_languages['setting']['locale'];
    
        // conditions for not attempting anything
        if ( $locale_pref == $this->_locale_pref )
            return true;
    
        $locale_tests = array(&$locale_pref, 
                              &$_SERVER['HTTP_HOST'], 
                              PROJECT_NAME);
    
        // test to see if we can set to some default in order of the array
        foreach ( $locale_tests as $test )
        {
            if ( isset($this->_all_languages['locale'][$test]) ) {
                $this->_locale_pref = $test;
                return true;
            }
        }
    
	// NOTE: I have gone back and forth on whether or not to set this
	// I think it is wisest to set as last precaution to the default
	// and ideally also make some note in the error log stating what is up
	$this->_locale_pref = DEFAULT_LOCALE_PREF;
        return false;
    }
    
    function setLanguage ($lang_pref = DEFAULT_LANG)
    {
        $lang_possible = 
            &$this->_all_languages['locale'][$this->_locale_pref]['language'];
    
        if ( $lang_pref == $this->_language )
            return true;
    
        $lang_tests = array(&$lang_pref, 
                            $lang_pref . "_" . strtoupper($lang_pref));
    
        // test to see if we can set to some default in order of the array
        foreach ( $lang_tests as $test )
        {
            if ( isset($lang_possible[$test]) ) {
                $this->_language = $test;
                return true;
            }
        }
    
        // if all else fails set it to the default
        // $lang_setting = DEFAULT_LANG;
        return false;
    }
   
    function setDomain ($domain = DEFAULT_DOMAIN)
    {
        $this->_domain = $domain;
    }
   
    function init ()
    {
        putenv("LANG=" . $this->_language ); 
        setlocale(LC_ALL, $this->_language );
        bindtextdomain($this->_domain, 
	               DEFAULT_LOCALE . "/" . $this->_locale_pref );
        textdomain($this->_domain);
    }
    
    function debugLanguages ()
    {
        echo "<pre>";
        print_r( $this->_all_languages );
	print_r( $this );
        echo "</pre>";
    }
    

    function getAllLanguages ()
    {
        return $this->_all_languages;
    }

    function getLocale ()
    {
        return $this->_locale_pref;
    }

    function getLanguage()
    {
        return $this->_language;
    }

    function getPossibleLanguages()
    {
	return $this->_all_languages['locale'][$this->_locale_pref]['language'];
    }

    function getPossibleLocalePrefs()
    {
	return $this->_all_languages['locale'];
    }

    function getDomain()
    {
        return $this->_domain;
    }
} // end of class CCLanguage()

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

// This nastiness handles session storage 
$ccLang = &$_SESSION['lang'];

if ( ! isset($ccLang) || isset($_REQUEST['update'] ) ) {
    $ccLang = new CCLanguage(&$_REQUEST['lang']);
    if (DEBUG) echo "<p>created new object</p>";
}
else 
{
    if ( isset($_REQUEST['lang']) ) {
        $ccLang->setLanguage(&$_REQUEST['lang']);
        if (DEBUG) echo "<p>set new language</p>";
    }

    if ( isset($_REQUEST['localepref']) ) {
        $ccLang->setLocalePref(&$_REQUEST['localepref']);
        if (DEBUG) echo "<p>set new locale pref</p>";
    }

    if (DEBUG) echo "<p>Using session language</p>";
}

// $ccLang->debugLanguages();

$ccLang->init();

// START OF REAL CONTENT

echo "<h3>FILENAME: " . $_SERVER['PHP_SELF'] . "</h3>\n";
?>

<h4>Select Locale Preference</h4>

<?php
echo "Current Locale Preference: <b>" . $ccLang->getLocale() . "</b>\n";
echo "<ul>\n";

foreach ( $ccLang->getPossibleLocalePrefs() as $key => $value )
{
    echo "<li><a href=\"?localepref=$key\">$key</a></li>\n";
}
?>
</ul>

<h4>Select Language</h4>

<?php
echo "Current Language: <b>" . $ccLang->getLanguage() . "</b>\n";
echo "<ul>\n";

foreach ( $ccLang->getPossibleLanguages() as $lang => $value )
{
    echo "<li><a href=\"?lang=$lang\">$lang</a></li>\n";
}
?>
</ul>

