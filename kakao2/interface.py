import requests
import json
import time
import random
import pickle
import pdb

master_token = "346aa2ae35423b26e443ebc9bac7bf90"
base = "https://pegkq2svv6.execute-api.ap-northeast-2.amazonaws.com/prod/users"

dy = [-1,0,1,0]
dx = [0,1,0,-1]

class interface:
    def __init__(self, problem):
        self.problem = problem
        r = requests.post("{}/start".format(base), headers={"X-Auth-Token":master_token},
                          params={"problem":self.problem}).json()
        self.token = r['auth_key']
        print("start", r)
        self.bd_size = 0
        self.truck_size = 0
        self.default = 0
        if self.problem == 1:
            self.bd_size = 5
            self.truck_size = 5
            self.default = 4
        elif self.problem == 2:
            self.bd_size = 60
            self.truck_size = 10
            self.default = 3
        else:
            print("Invaild problem!!!!!!!!!!!")
        self.bd = [[0]*self.bd_size for i in range(self.bd_size)]
        self.prob = [[self.default] * self.bd_size for i in range(self.bd_size)]
        self.t = []
        self.cmd = []

    def _update_prob(self,bd):
        mx = 0
        for i in range(self.bd_size):
            for j in range(self.bd_size):
                mx = bd[i][j] if bd[i][j] > mx else mx
        for i in range(self.bd_size):
            for j in range(self.bd_size):
                tmp = mx - bd[i][j]
                th = 1
                self.prob[i][j] = tmp if tmp >= th else th


    def _get_pos(self, id):
        r = -(id % self.bd_size - (self.bd_size - 1))
        c = id // self.bd_size
        return (r,c)

    def _get_id(self, r, c):
        return (self.bd_size - 1 -r) + c*self.bd_size

    def locations(self):
        r = requests.get("{}/locations".format(base), headers={"Authorization": self.token}).json()
        print("[locations]",r)
        for i in r["locations"]:
            (r,c) = self._get_pos(i["id"])
            self.bd[r][c] = i["located_bikes_count"]

    def trucks(self):
        r = requests.get("{}/trucks".format(base), headers={"Authorization": self.token}).json()
        print("[trucks]",r)
        self.t = r["trucks"]
        print("truck pos")
        for i in self.t:
            (r,c) = self._get_pos(i["location_id"])
            print(i["id"],":", r,c)


    def get_score(self):
        r = requests.get("{}/score".format(base), headers={"Authorization": self.token}).json()
        print(r["score"])
        return r["score"]

    def _job(self):
        for truck in self.t:
            tid = truck['id']
            (r, c) = self._get_pos(truck["location_id"])
            tmp = []
            loaded = truck['loaded_bikes_count']
            while len(tmp) < 10:
                diff = self.bd[r][c] - self.prob[r][c]
                if diff > 0 and loaded < 20:
                    cnt = diff if loaded + diff < 20 else 20 - loaded
                    for i in range(cnt):
                        if len(tmp) >= 10:
                            break
                        tmp.append(5)
                        self.bd[r][c] -= 1
                        loaded -= 1
                elif diff < 0 and loaded > 0:
                    cnt = loaded if loaded < abs(diff) else abs(diff)
                    for i in range(cnt):
                        if len(tmp) >= 10:
                            break
                        tmp.append(6)
                        self.bd[r][c] += 1
                        loaded += 1

                if len(tmp) < 10:
                    for di in range(4):
                        ny = r + dy[di]
                        nx = c + dx[di]
                        if ny < 0 or nx < 0 or ny >= self.bd_size or nx >= self.bd_size:
                            continue
                        diff = self.bd[ny][nx] - self.prob[ny][nx]
                        if diff > 0 and loaded < 20:
                            tmp.append(di+1)
                            r, c = ny, nx
                        elif diff < 0 and loaded > 0:
                            r,c = ny,nx
                            tmp.append(di+1)
                        else:
                            rand = random.randrange(1, 5)
                            tmp.append(rand)
                        break
                if tmp[-1] == 0:
                    break

            self.cmd[tid]['command'] = tmp


    def _cmd(self):
        self.cmd.clear()
        for i in range(self.truck_size):
            self.cmd.append({"truck_id": i, "command": []})
        #print("[prob]", self.prob)
        self._job()
        print("[_cmd][cmd]", self.cmd)
        r = requests.put("{}/simulate".format(base), headers={"Authorization": self.token},
                         data=json.dumps({"commands": self.cmd})).json()
        print("[_cmd]", r)