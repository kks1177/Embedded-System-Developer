# import threading
# from playsound import playsound

# class SoundClass():
#     def __init__(self, filename):
#         self.filename = filename
#         self.playsoundth = None

#     def play(self):
#         if(self.playsoundth is not None and self.playsoundth.is_alive()):
#             print(1)
#             return
#         self.playsoundth = threading.Thread(target=playsound, args=(self.filename,))
#         self.playsoundth.setDaemon(True)
#         self.playsoundth.start()

from pygame import mixer
import multiprocessing
import time

class SoundClass():
    filename = ""

    def __init__(self, max_channels = 10):
        self.max_channels = max_channels

    def play(self, filename):
        _ = multiprocessing.Process(target=self._play, kwargs={"filename":filename})
        _.start()

    def _play(self, filename):
        mixer.init()
        mixer.set_num_channels(self.max_channels)
        for i in range(self.max_channels):
            if(not mixer.Channel(i).get_busy()):
                # print(filename, i)
                mixer.Channel(i).play(mixer.Sound(filename))
                break
        
        # 사운드 재생이 끝날 때까지 프로세스를 종료하지 않고 대기함
        # (프로세스가 종료되면 사운드도 같이 꺼지기 때문)
        while(mixer.Channel(i).get_busy()):
            time.sleep(1)
        time.sleep(1)
        
        