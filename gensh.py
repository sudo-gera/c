from h import *
import genshin

async def code():
	client = genshin.Client({'ltuid':'101242997', 'ltoken':'UWX4TzbK8qLXZ3Y8Ist1OwCv4jz7Ne9n1z12UA61'},lang="ru-ru")
	client.default_game=genshin.Game.GENSHIN

	try:
		reward = await client.claim_daily_reward()
	except genshin.AlreadyClaimed:
		print("Daily reward already claimed")
	else:
		print(f"Claimed {reward.amount}x {reward.name}")


async def main():
	while 1:
	    print(asctime())
	    try:
	        await code()
	    except:
	        print(format_exc())
	    print(asctime())
	    sleep(3600*12)

asyncio.run(main())
