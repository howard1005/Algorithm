from interface import interface
import time
import pickle
import os.path
import pdb

p = 2
bd_path = 'bd{}'.format(p)
log_path = 'log{}.txt'.format(p)

def update(data):
    with open(bd_path, 'wb') as f:
        pickle.dump(data, f)

def load():
    if not os.path.isfile(bd_path):
        return []
    with open('bd{}'.format(p), 'rb') as file:
        while True:
            try:
                data = pickle.load(file)
                print(data)
                return data
            except EOFError:
                break
    return []

def main():
    for cnt in range(100):
        I = interface(p)
        data = load()
        if len(data):
            I._update_prob(data)
        for i in range(720):
            I.locations()
            I.trucks()
            I._cmd()
        score = I.get_score()
        f = open(log_path, 'a')
        f.write("{}\n".format(score))
        f.close()
        update(I.bd)


if __name__ == "__main__":
    main()