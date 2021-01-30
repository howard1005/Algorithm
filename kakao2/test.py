import requests
import pdb

print(requests.delete("https://httpbin.org/delete").json())
print(requests.get("https://httpbin.org/get").json())
print(requests.patch("https://httpbin.org/patch").json())
print(requests.post("https://httpbin.org/post").json())
print(requests.put("https://httpbin.org/put").json())
pdb.set_trace()