/**
* Copyright (c) 2016 Gabriel Ferreira <gabrielinuz@gmail.com>. All rights reserved. 
* Released under the MIT license
* https://opensource.org/licenses/MIT
**/
document.addEventListener('DOMContentLoaded', function () 
{
    var btn = document.getElementById("execButton1");
    btn.addEventListener("click", function()
    {
        function fillOutput(response)
        {
            document.getElementById("response1").value = response.data[0]['greeting'];
        }

        var request1 = new RequestWrapper(new XMLHttpRequest());
        request1.path = 'backend/main.exe';
        request1.callback = fillOutput;
        request1.appendParameter('action', 'TestRequestResponse');
        request1.appendParameter('greeting', document.getElementById("greet1").value);
        request1.send();
    });  

    var btn2 = document.getElementById("execButton2");
    btn2.addEventListener("click", function()
    {
        function fillOutput2(response)
        {
            document.getElementById("response2").value = response.data[0]['greeting'];
        }

        var request2 = new RequestWrapper(new XMLHttpRequest());
        request2.path = 'backend/main.exe';
        request2.callback = fillOutput2;
        request2.appendParameter('action', 'TestRequestResponse');
        request2.appendParameter('greeting', document.getElementById("greet2").value);

        request2.send();
    });  
});