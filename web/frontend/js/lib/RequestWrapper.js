/**
* Copyright (c) 2016 Gabriel Ferreira <gabrielinuz@gmail.com>. All rights reserved. 
* Released under the MIT license
* https://opensource.org/licenses/MIT
**/

/**
* Constructor function
*/
function RequestWrapper(requestObject) 
{  
    this._requestObject = requestObject; 
    this._parameters = '';
    this._method = 'GET';
    this._asynchronous = true;
    this._responseType = 'json';
}

/*PROPERTIES:*/
Object.defineProperties(RequestWrapper.prototype, 
{
    method: 
    {
        get: function () 
        {
            return this._method;
        },
        set: function (method) 
        {
            this._method = method;
        }
    }
});

Object.defineProperties(RequestWrapper.prototype, 
{
    path: 
    {
        get: function () 
        {
            return this._path;
        },
        set: function (path) 
        {
            this._path = path;
        }
    }
});

Object.defineProperties(RequestWrapper.prototype, 
{
    asynchronous: 
    {
        get: function () 
        {
            return this._asynchronous;
        },
        set: function (asynchronous) 
        {
            this._asynchronous = asynchronous;
        }
    }
});

Object.defineProperties(RequestWrapper.prototype, 
{
    url: 
    {
        get: function () 
        {
            return this._url;
        },
        set: function (url) 
        {
            this._url = url;
        }
    }
});

Object.defineProperties(RequestWrapper.prototype, 
{
    callback: 
    {
        get: function () 
        {
            return this._callback;
        },
        set: function (callback) 
        {
            this._callback = callback;
        }
    }
});

Object.defineProperties(RequestWrapper.prototype, 
{
    responseType: 
    {
        get: function () 
        {
            return this._responseType;
        },
        set: function (responseType) 
        {
            this._responseType = responseType;
        }
    }
});


RequestWrapper.prototype.appendParameter = function(key, value)
{
    key = (key) ? key : console.error('The key parameter can not be null!');
    value = (value) ? value : console.error('The value parameter can not be null!');
    this._parameters += key + '=' + value + '&'; 
};

RequestWrapper.prototype._generateUrl = function(key, value)
{
    this._parameters = this._parameters.slice(0, -1);
    this._url = this._path + '?' + this._parameters;
};

RequestWrapper.prototype.send = function()
{
    this._generateUrl();   
    this._requestObject.open(this._method, this._url, this._asynchronous);
    this._requestObject.send();
    this._requestObject.responseType = this._responseType;

    var self = this;
    this._requestObject.onreadystatechange = function() 
    {
        if (self._requestObject.readyState === 4) 
        {
            if (self._requestObject.status === 200) 
            {
                self._callback(self._requestObject.response);
            } 
            else 
            {
                console.error(self._requestObject.statusText);
            }
        }
    };

    this._requestObject.onerror = function() 
    {
        console.error(self._requestObject.statusText);
    };
};