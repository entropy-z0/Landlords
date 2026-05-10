import json
import requests

def request_post(url, param):
    headers = {'content-type': 'application/json'}
    ret = requests.post(url, json=param, headers=headers, timeout=10)
    return json.loads(ret.text)

post_url = "http://47.115.62.20:3002"
request_param = {
  "action": "init",
  "data": {
    "three_landlord_cards": "444",
    "pid": 10001,
    "ai_amount": 2,
    "player_data": [
      {
        "model": "WP",
        "hand_cards": "333444456789TJQKA2XD",
        "position_code": 1
      },
      {
        "model": "WP",
        "hand_cards": "3555666777888999T",
        "position_code": 2
      }
    ]
  }
}
a = request_post(post_url, request_param)

print(a)

