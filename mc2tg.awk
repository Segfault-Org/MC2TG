#!/bin/awk -f
BEGIN {
	printf "The bot is starting.\n"
}

{
	match($0, /.*\[([0-9][0-9]:[0-9][0-9]:[0-9][0-9])\] \[(.*)\/(.*)\]: (.*)/, line);
	time = line[1];
	tag = line[2];
	level = line[3];
	data = line[4];

	if(tag == "Server thread" && level == "INFO")
	{
		if(data ~ /.* joined the game/ ||
		   data ~ /.* lost connection: .*/ ||
		   data ~ /<.*> .*/)
		{
			if(data !~ /.*com.*mojang.*authlib.*GameProfile.*/)
			{
				printf "（测试，旧消息）[%s] %s\n", time, data;
			}
		}
	}
}

END {
	printf "The server stops, or the pipe reaches EOF.\n"
}
