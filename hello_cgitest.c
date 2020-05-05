// Compile with: gcc hello_cgitest.c -o hello_cgitest.fcgi -lfcgi -Wl,-rpath /usr/local/lib
#include <fcgi_stdio.h>
#include <stdlib.h>
#include <string.h>

int main (void) {
	unsigned char val = 0;
	int sum, num1,num2;
	char *env;
	num1=0;num2=0;sum=0;

	while(FCGI_Accept() >= 0){
		printf("Status: 200 OK\r\n");
		printf("Content-type: text/html\r\n\r\n");
		printf("<!doctype><html>");
		printf("<head><meta http-equiv=\"refresh\" content=\"3\"</head> <body>");
		printf("val %d<br>", val);

		env=getenv("HTTP_USER_AGENT");
		if(env != NULL) {
			printf("User Agent = %s<br>",env);
		}
		
		env=getenv("CONTENT_TYPE");
		if(env != NULL) {
			printf("Content Type = %s<br>",env);
		}

		printf("</body></html>\n");
		val++;
		
		/*for post*/
		printf("<!doctype> \
			<html> <body> <form method=\"post\" action=\"\"> \
					<label for=\"fno\">Number1:</label><br> \
				 	<input type=\"number\" id=\"fno\" name=\"fno\" value=%d><br> \
		  			<label for=\"lno\">Number2:</label><br> \
		  			<input type=\"number\" id=\"ln0\" name=\"ln0\" value=%d><br><br> \
		  			<input type=\"submit\" value=\"Submit\"> \
				</form> \
				Sum = %d\
			</body> \
			</html><br>",num1,num2,sum);
		env=getenv("REQUEST_METHOD");
		if(strcmp(env, "POST") == 0) 
		{
			char buffer[200] = {'\0'};
			const char delim[] = "&=";
   			char *token;
			int tokenNo=0;
			int inputlen = atoi(getenv("CONTENT_LENGTH"));
			fread(buffer, inputlen, 1, stdin);
			/*parse input  fno=4&ln0=-2 */
			token = strtok(buffer, delim);
			while(token!= NULL)
			{
				tokenNo++;
				if(2 == tokenNo) num1=atoi(token);
				if(4 == tokenNo) num2=atoi(token);
				token = strtok (NULL, delim);
			}
			sum = num1+num2;
		}
	}		


    return EXIT_SUCCESS;
}
