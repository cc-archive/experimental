<html>
<head>
    <title>Hello</title>
    <style>
    <!--
    form#license_selection {
        border: 1px solid gray;
    }
    #output {
        border: 1px solid gray;
    }
    textarea#test {
        height: 20%;
        width: 100%;
    }
    -->
    </style>
<script type="text/javascript" language="javascript" src="../cclib/js/prototype.js"></script>
<script type="text/javascript" language="javascript" src="../cclib/js/cc-lib-freedoms.js"></script>
<script language="javascript">
var freedoms;

/*
Event.observe(freedoms, 'change', $('share'), false);
Event.observe(freedoms, 'change', $('share'), false);
Event.observe(freedoms, 'change', $('share'), false);
Event.observe(freedoms, 'change', $('share'), false);

Event.observe(freedoms, 'change', $('output'), false);
*/
function init ()
{
    /* THIS IS ALL EXPERIMENTS IN GETTING EVENTS TO WORK RIGHT */
    // $('share').checked = true;
    // $('remix').checked = true;

    // Event.observe('test', 'change', function (event) { $('output').innerHTML = $('test').value }, false );
    // Event.observe('test', 'change', freedoms, false );
    //Event.observe('share', 'click', function (event) { alert('selected');}, 
    //              false );

    /* Event.observe('share', 'click', function (event) { alert(Event.element(event));}, 
                  false );
    */
}

    // obj.innerHTML = Event.element(event);

</script>

</head>
<body onload="freedoms = new CCLibFreedoms(); init();">

<script>

</script>

<textarea name="test" id="test">
</textarea>


<form id="license_selection" action="">


<input type="checkbox" id="share" value="" name="share" onchange="freedoms.redo('share')" /><label for="share">Allow Share</label>
<br />

<input type="checkbox" id="nc" value="" name="nc" onchange="freedoms.redo('nc')" /><label for="nc">Prohibit Commercial Use
</label>
<br />

<input type="checkbox" id="remix" value="" name="remix" onchange="freedoms.redo('remix')" /><label for="remix">Allow Remix</label>
<br />

<input type="checkbox" id="sa" value="" name="sa" onchange="freedoms.redo('sa')" />
<label for="sa">Require Share-Alike</label>
<br />


</form>

<div id="output">
Output will go here and probably replace this.

</div>


</body>
</html>

