#!/usr/bin/env python
# author: liudeji
import time, RPi.GPIO as GPIO
import urllib
import serial
import time,sys
def  program():
    rebootCount=0
    def fetch_thing(url, params, method):
        params = urllib.urlencode(params)
        if method=='POST':
            f = urllib.urlopen(url, params)
        else:
            f = urllib.urlopen(url+'?'+params)
        return (f.read(), f.code)
    def catchHtml():
        url="http://192.168.191.1:8080/webApp/fetch.action"
        postdata=urllib.urlencode({'userid':1,'deviceId':1})
        postdata=postdata.encode('utf-8')
        res=urllib.urlopen(url,postdata)
        re=res.read()
        mystr=re.decode("utf-8")
        return mystr
  
    ser=serial.Serial('/dev/ttyACM0', 9600, timeout=1)
    ser.write("")
    while 1:
        ser.write(catchHtml())
        n=0
        t=0
        u=0
        i=0
        l=0
        a=[0 for i in range(9)]
        data=[0 for i in range(4)]
        data[3]=None
        p=ser.readline()
        if(len(p)!=0 and p[0]=='H' and p[1]!='H' and p[-1]=='\n' ):
            print(p)
            for i in range(0,len(p)):
                if(p[i]==','):
                    a[u]=p[t:i]
                    t=i+1
                    u=u+1
                elif(i==len(p)-1):
                    a[u]=p[t:len(p)-2]
            for i in range(0,9):
                if(i%2!=0):
                    if(int(a[i+1])==0):
                        n=float(a[i])
                        data[l]=n
                        l=l+1
                        print(n)
                    else:
                        n=float(a[i])/float(a[i+1])
                        data[l]=n
                        l=l+1
                        print(n)
                if(data[3]!=None):
                    print(data[1])
                    content, response_code = fetch_thing(
                                     'http://192.168.191.1:8080/webApp/insertData.action',
                                     {'userid': 1, 'dataValue': data[0],'deviceId':4},
                                     'GET'
                                     )
                
                    content, response_code = fetch_thing(
                                     'http://192.168.191.1:8080/webApp/insertData.action',
                                     {'userid': 1, 'dataValue': data[1],'deviceId':3},
                                     'GET'
                                     )
                    content, response_code = fetch_thing(
                                     'http://192.168.191.1:8080/webApp/insertData.action',
                                     {'userid': 1, 'dataValue': data[2],'deviceId':16},
                                     'GET'
                                     )
                    data[3]=None
                    time.sleep(3)
        else:
            rebootCount=rebootCount+1
            ser.write("")
            print("wating for data:")
            time.sleep(3)
            if(rebootCount==3):
                print("restart...")
                time.sleep(4)
                program()
program()
         
        


