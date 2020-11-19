#include "common.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <curl/curl.h>

#define BASE_URL "https://api.telegram.org/bot"
#define BASE_URL_SEND "/sendMessage"

char *tgChat;
char *url;
CURL *curl;

int tg_send(const char *string);

int main(int argc, char **argv)
{
	if(getenv("TG_KEY") == NULL)
	{
		fprintf(stderr, _("TG_KEY env does not present.\n"));
		return EX_USAGE;
	}
	if(getenv("TG_CHAT") == NULL)
	{
		fprintf(stderr, _("TG_CHAT env does not present.\n"));
		return EX_USAGE;
	}
	curl = curl_easy_init();

	tgChat = getenv("TG_CHAT");

	char u[strlen(BASE_URL) + strlen(getenv("TG_KEY")) + strlen(BASE_URL_SEND) + 1];
	strcpy(u, BASE_URL);
	strcat(u, getenv("TG_KEY"));
	strcat(u, BASE_URL_SEND);
	url = u;

start: ;
	const char str[501];
	if(fgets((char*)str, 500, stdin) == NULL)
	{
		goto stop;
	}

	int r = tg_send(str);

	if(r)
	{
		goto stop;
	}
	goto start;
stop: ;
	if(curl != NULL)
	curl_easy_cleanup(curl);
	return r;
}

int tg_send(const char *string)
{
	char *strCurlEncoded = curl_easy_escape(curl, string, 0);
	char finalurl[strlen(url) + strlen("?chat_id=") + strlen(tgChat) + strlen("&text=") + strlen(strCurlEncoded) + 1];
	strcpy(finalurl, url);
	strcat(finalurl, "?chat_id=");
	strcat(finalurl, tgChat);
	strcat(finalurl, "&text=");
	strcat(finalurl, strCurlEncoded);
	curl_easy_setopt(curl, CURLOPT_URL, finalurl);
	CURLcode res = curl_easy_perform(curl);
	curl_free(strCurlEncoded);
	long httpCode = -1;
	curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &httpCode);
	if(res || httpCode != 200)
	{
		fprintf(stderr, _("Cannot post the message. CURL result %u, HTTP code %lu. Check if your Bot API Key and Chat ID is correct, or your network connectivity is good, and try again. \n"), 
				res, 
				httpCode);
	}
	return 0;
}
