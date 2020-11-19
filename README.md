# MC2TG

Forward Minecraft server chat and user join / leave messages to Telegram.

## Usage

Pipe the logs to the bot.

If you are using Docker:

```shell
docker logs <container> -f --tail 0 | awk -f mc2tg.awk | TG_KEY=<Telegram bot key> TG_CHAT=<Telegram chat> mc2tg-bot
```

## License
Author Trumeet <i@yuuta.moe>

License: GPL v2 only
