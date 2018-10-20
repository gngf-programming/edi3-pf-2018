// Jonathan Egea, Leonardo Casales - Edi3

// pqConnect pq( "localhost", "5432", "compset","postgres", "root" ) ;
// pq.Connect() ;
// pq.Show( 'users' );
// pq.Disconnect() ;

#ifndef pqConnect_hpp
#define pqConnect_hpp

#include <stdio.h>
#include <libpq-fe.h>

class pqConnect {
private:
    char* host ;
    char* dataBase ;
    char* port ;
    char* user ;
    char* passwd ;
    PGconn *cnn ;
    PGresult *result ;
    bool connected ;
    
public:
    pqConnect () ;
    pqConnect ( char* host, char* port, char* dataBase, char* user, char* passwd ) ;
    bool Connect() ;
    void Disconnect() ;
    int Show( char* table ) ;
};
#endif /* pqConnect_hpp */

pqConnect::pqConnect() {
    PGconn *cnn = NULL;
    PGresult *result = NULL;
}

pqConnect::pqConnect ( char* Host, char* Port, char* DataBase, char* User, char* Passwd ) {
    PGconn *cnn = NULL;
    PGresult *result = NULL;
    host = Host ;
    dataBase = DataBase ;
    port = Port ;
    user = User ;
    passwd = Passwd ;
}

bool pqConnect::Connect() {
	cnn = PQsetdbLogin(host,port,NULL,NULL,dataBase,user,passwd);
    if (PQstatus(cnn) != CONNECTION_BAD) {
        printf( "Estamos conectados a PostgreSQL!<br>\n" ) ; 
        connected = true ;
        result = PQexec(cnn, "");
	} else {
		printf( "Error de conexion!<br>\n" ) ;
		PQfinish(cnn) ;
		connected = false ;
	}
	return connected ;

}

int pqConnect::Show( char* table ) {

    int i = 0 ;
    char cSQL[] = "SELECT * FROM " ;
    
    int length = 14 ;
    while (table[i] != '\0' ){
        cSQL[length] = table[i];
        length ++;
        i++;
    }
    cSQL[length] = '\0';
    
    printf( "%s<br>\n", cSQL ) ;
    
    
    if (connected ) {
        
        result = PQexec(cnn, cSQL);
        
        if (result != NULL) {
            int tuplas = PQntuples(result);
            int campos = PQnfields(result);
            printf( "No. Filas: %i<br>\n", tuplas ) ;
            printf( "No. Campos:%i<br>\n", campos ) ;
            
            printf( "Los nombres de los campos son:<br>\n" ) ;
            
            for (i=0; i<campos; i++) {
                printf( "%s | ", PQfname(result,i) ) ;
            }
            
            printf( "Contenido de la tabla<br>\n" ) ;
            
            for (i=0; i<tuplas; i++) {
                for (int j=0; j<campos; j++) {
                    printf( "%s | ",PQgetvalue(result,i,j) );
                }
                printf ( "<br>\n" ) ;
            }
        }
        return true ;
        // Ahora nos toca liberar la memoria
        //PQclear(result);
        
    } else {
        printf( "Error de conexion\n" );
        return false ;
    }

}

void pqConnect::Disconnect() {
	if (connected ) {
    	PQclear(result);
    	PQfinish(cnn);
	}
}