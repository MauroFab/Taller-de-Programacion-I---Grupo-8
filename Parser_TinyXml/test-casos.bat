echo ----------------------------------------------------------------------
copy .\Debug\Parser_TinyXml2.exe Parser_TinyXml2.exe

echo ----------------------------------------------------------------------
@rem OK
Parser_TinyXml2.exe cliente.xml

echo ----------------------------------------------------------------------
@rem ERROR, esta vacio
Parser_TinyXml2.exe cliente-caso-00.xml

echo ----------------------------------------------------------------------
@rem ERROR cliente vacio
Parser_TinyXml2.exe cliente-caso-01.xml

echo ----------------------------------------------------------------------
@rem OK 
Parser_TinyXml2.exe cliente-caso-02.xml

echo ----------------------------------------------------------------------
@rem ERROR, un tag valor repetido
Parser_TinyXml2.exe cliente-caso-03.xml

echo ----------------------------------------------------------------------
@rem ERROR, puerto repetido en conezion
Parser_TinyXml2.exe cliente-caso-04.xml

echo ----------------------------------------------------------------------
@rem ERROR conexion repetido
Parser_TinyXml2.exe cliente-caso-05.xml

echo ----------------------------------------------------------------------
@rem ERROR cliente repetido
Parser_TinyXml2.exe cliente-caso-06.xml

echo ----------------------------------------------------------------------
@rem ERROR ip repetido en conexion
Parser_TinyXml2.exe cliente-caso-07.xml

echo ----------------------------------------------------------------------
@rem ERROR falta tag conexion
Parser_TinyXml2.exe cliente-caso-08.xml

echo ----------------------------------------------------------------------
@rem ERROR lista de <mensajes> vacia
Parser_TinyXml2.exe cliente-caso-09.xml

echo ----------------------------------------------------------------------
@rem ERROR falta el tag <mensajes>
Parser_TinyXml2.exe cliente-caso-10.xml

echo ----------------------------------------------------------------------
@rem ERROR falta el tag cierre de un mensaje </mensaje>
rem Parser_TinyXml2.exe cliente-caso-11.xml

echo ----------------------------------------------------------------------
@rem ERROR es case sensitive para el tag <MENSAJE> vs <mensaje>
Parser_TinyXml2.exe cliente-caso-12.xml

echo ----------------------------------------------------------------------
@rem ERROR 
Parser_TinyXml2.exe cliente-caso-13.xml

echo ----------------------------------------------------------------------
@rem ERROR 
Parser_TinyXml2.exe cliente-caso-14.xml

echo ----------------------------------------------------------------------
@rem ERROR 
Parser_TinyXml2.exe cliente-caso-15.xml

echo ----------------------------------------------------------------------
@rem OK, pero es largo 
Parser_TinyXml2.exe cliente-caso-15.xml

echo ----------------------------------------------------------------------