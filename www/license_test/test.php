<?php

/*
if ( ! $dom = domxml_open_file('licenses.xml') )
    echo "error";

$root = $dom->document_element(); */


$doc = new DOMDocument()
$doc->load('licenses.xml');
// echo $doc->saveXML();
print_r($doc) ;

$doc->getElementsByTagName('jurisdiction');


?>
<html>
<script type="text/javascript" language="javascript">
<!--

function load_xml_url (url)
{
    var req = new XMLHttpRequest();
    req.open("GET", url, false);
    req.send(null);

    return req.responseXML;
}

function get_jurisdictions ()
{
    var xmlDoc = 
        load_xml_url("http://cclabs.localhost/licensechooser/licenses.xml");

    return xmlDoc.evaluate('//jurisdictions', xmlDoc, null, 
                           XPathResult.ANY_TYPE, null);

}

function test_jurisdictions ()
{
    var jurisdictions = get_jurisdictions();
    var alertText = '' + jurisdictions;
    /*
    while (jurisdictions) {
        alertText += jurisdictions.textContent + "\n";
        jurisdictions.iterateNext();
    }*/
    alert(alertText);
}


/*
class DHTMLLicense extends Object
{
    function constructor ()
    {
    }
}

var dhtmlLicense = new DHTMLLicense();
*/

-->
</script>
<body>


<p><a href="#" onclick="test_jurisdictions();">Test</a></p>

</body>
</html>



