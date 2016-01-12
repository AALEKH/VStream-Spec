# VStream-Spec

VSTREAM is supposed to be REST architecture based binary protocl which sends Velocypack Bytes to communicate.

VStream structure will be as follow:

```
struct vstream{
long long int id;
long int sub_id;
int tob;
string method;
time_t date;
int cached;
};
```

Specifications for VStream Protocol

      +---------+---------+--------------------+---------+------+--------+
      | ID      |  SUB-ID |  TOB               | METHOD  | Date | Cached |
      +---------+---------+--------------------+---------+------+--------+
      |                                                                  |
      .                       VelocyPack(body)                           .
      .                                                                  .
      .                                                                  .
      +------------------------------------------------------------------+
      
## ID

A Positive/Negative signed integer value and contains a unique, client/server-side ID. For a given request, response will contain the 
same ID field. If a given Id is positive it is supposed to have arrived from Client side, whereas of the request id is negative it
is supposed to be coming from server side. For a given request(arangodb query or uri) the ID is unique

## SUB-ID

For a given request, response might be of several part ( multi-part response ) in order to have multi part response in a proper
order "sub-id" will be used, for ex: for request id : 85127, response (having 3 multi part response) will have id and sub id as
-85127 and (1, 2, 3).

## TOB (Type Of Byte)

TOB or Type Of Byte will help us determine the whether the Byte sent is request or response, this Request-Response model is valid for both Byte sent from Server or Client. 1->request; 0->response.

## METHOD

This Contains VStream Methods, defined methods include:

#### 1) AUTH
#### 2) CRED
#### 3) GET
#### 4) POST
#### 5) DELETE
#### 6) HEAD
#### 7) PATCH
#### 8) REGISTER
#### 9) status

This method is used for response of CRED ; 1 if the CRED seems to verify, 0 if not. Further, the VelcoyPack(body) will contain 0x00 value.

### 2) CRED

This method is used for sending Authentication request; contains VelocyPack(body) as "0x07", where first byte will correspong to 
username and second to password.

### 3) GET

This method is used to retrieve some VelocyPack byte depending on query/uri requested.

### 4) DELETE

This method is used to issue DELETE request, this particular method is valuable in case of BLOB object resource request.

### 5) HEAD

This Method is used to retieve meta data information about a particular request, for example: presence of a row, presence of 
file, size of file, date of creation of row, etc;

### 6) PATCH

This Method functions as Update request for a particlar row, file (blob).

### 7) REGISTER [Optional]

This Method is used for registering event of some kind, for ex: retrieve a row at 3:00 PM ( sort fo CRON job task).

### 8) STATUS

Returns STATUS code and message for a given request,for ex: this method will be returned by the bytes along error code and string explaining the error.
Its body is of "0X07" type VelocyPack byte.

#### 9) POST

Used to insert some form of VelocyPack bytes into arangodb.

==

## ERROR CODES

example error codes include: 200, 404 (for invalid request), 500 (resource not available)...much more on these to be decided as per implementation.


## Cached

This determines whether the request needs to be cached or not. 0-> yes; 1 -> no.

