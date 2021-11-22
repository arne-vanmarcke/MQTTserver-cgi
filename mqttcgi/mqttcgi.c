/*******************************************************************************
 * Copyright (c) 2012, 2017 IBM Corp.
 *
 * All rights reserved. This program and the accompanying materials
 * are made available under the terms of the Eclipse Public License v1.0
 * and Eclipse Distribution License v1.0 which accompany this distribution. 
 *
 * The Eclipse Public License is available at 
 *   http://www.eclipse.org/legal/epl-v10.html
 * and the Eclipse Distribution License is available at 
 *   http://www.eclipse.org/org/documents/edl-v10.php.
 *
 * Contributors:
 *    Ian Craggs - initial contribution
 *******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql.h>

MYSQL *con;

void finish_with_error(MYSQL *con)
{
  fprintf(stderr, "%s\n", mysql_error(con));
  mysql_close(con);
  exit(1);
}

MYSQL_RES * mysql_get_rows()
{
    if(mysql_query(con, "SELECT temp, time FROM temperatures ORDER BY time DESC LIMIT 10") !=0)
    {
        printf("Query failed  with the following message:\n");
        printf("%s\n", mysql_error(con));
        exit(1);
    }

    return mysql_store_result(con);

}

int main(int argc, char* argv[])
{
    MYSQL_RES *result;
    MYSQL_ROW row;
    int rc;
    int ch;

    con = mysql_init(NULL);

    if (con == NULL) 
    {
        fprintf(stderr, "%s\n", mysql_error(con));
        return -1;
    }

    if (mysql_real_connect(con, "localhost", "webuser", "secretpassword", "MQTT", 0, NULL, 0) == NULL) 
    {
        fprintf(stderr, "%s\n", mysql_error(con));
        mysql_close(con);
        return -1;
    }
    printf ("Content-type: text/html\n");
    printf ("\n");
    printf ("<HTML>\n"); 
    printf ("<HEAD>\n"); 
    printf ("<TITLE>MQTTCgi</TITLE>\n");
    printf("<STYLE>");
    printf("table,td,th{");
    printf("border: 1px solid #000000;");
    printf("text-align: left;");
    printf("}");
    printf("table{");
    printf("border-collapse: collapse;");
    printf("}");
    printf("</STYLE>");
    printf ("</HEAD>\n"); 
    printf ("<BODY>\n");
    printf ("<TABLE>\n");
    printf("<TR>");
    printf("<TH>Temp(&deg;C)</TH>");
    printf("<TH>Tijd</TH>");
    printf("</TR>");

    result=mysql_get_rows();
    while((row = mysql_fetch_row(result)) != NULL)
    {
        printf("<TR>");
        printf("<TD>%s</TD>",row[0]);
        printf("<TD>%s</TD>",row[1]);
        printf("</TR>");
    }
    printf ("</TABLE>\n");
    printf ("</BODY>\n");
    printf("<script>");
    printf("window.addEventListener('load',()=>{");
    printf("setTimeout(()=>{");
    printf("location.reload();");
    printf("},3000);");
    printf("})");
    printf("</script>");
    printf ("</HTML>\n");
    mysql_close(con);
    return (EXIT_SUCCESS);
}
