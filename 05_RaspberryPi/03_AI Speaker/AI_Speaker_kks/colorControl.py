import sys
import click

sys.path.insert(0, '/opt/wowlib/')

import configparser
import GoogleAssistantBlockly as talk

import board
import neopixel

# 동작에 필요한 변수 선언
pixels = None
config = None


# 네오 픽셀 초기화 함수      # 램프 초기화 함수
def init():
    global pixels

    pixels = neopixel.NeoPixel(board.D12, 8)  # 보드 D12에 연결, LED 개수 : 8개

    return pixels


# AI Speaker의 개별 LED 색상 제어 함수
def colorsetIdx(idx, red, green, blue):
    if pixels is not None:
        if (idx > 8):  # 총 8개의 LED 색상 제어 가능
            idx = 8

        pixels[idx] = (red, green, blue)


# AI Speaker의 모든 LED 색상 제어 함수
def colorset(red, green, blue):
    if pixels is not None:
        for i in range(0, 8):
            pixels[i] = (red, green, blue)


if __name__ == '__main__':

    config = configparser.ConfigParser()
    config.read('/opt/app/config.ini')

    settingRead = config['Setting']

    project_id = settingRead['Project ID']
    device_model_id = settingRead['Model ID']
    print("prjid:", project_id, " mdid:", device_model_id)

    assistant = talk.getAssistant(device_model_id, project_id, "ko-KR")
    device_handler = assistant.device_handler

    init()

    colorsetIdx(0, 66, 133, 244)
    colorsetIdx(1, 66, 133, 244)
    colorsetIdx(2, 66, 133, 244)
    colorsetIdx(3, 234, 67, 53)
    colorsetIdx(4, 234, 67, 53)
    colorsetIdx(5, 251, 188, 5)
    colorsetIdx(6, 251, 188, 5)
    colorsetIdx(7, 51, 168, 82)


    # 명령에 따른 LED 제어 설정
    @device_handler.command("com.example.commands.colorlamp")
    def colorlamp(colorlamp):
        if (colorlamp == "빨간색"):
            colorset(255, 0, 0)
        elif (colorlamp == "초록색"):
            colorset(0, 255, 0)
        elif (colorlamp == "파란색"):
            colorset(0, 0, 255)
        print("색상이 변경 되었습니다 : " + colorlamp)


    try:
        wait_for_user_trigger = True

        while (True):
            if wait_for_user_trigger:
                click.pause(info='Press Enter to send a new request...')

            (continue_conversation, record_message, audio_out_result, device_request) = assistant.assist()
            device_actions_futures = []
            fs = assistant.device_handler(device_request)

            if fs:
                device_actions_futures.extend(fs)

            print('Finished playing assistant response.')
            assistant.conversation_stream.start_playback()

            for batch in audio_out_result:
                assistant.conversation_stream.write(batch)
            assistant.conversation_stream.stop_playback()

            wait_for_user_trigger = not continue_conversation

    # 키보드 인터럽트 발생할 경우 종료
    except KeyboardInterrupt as e:
        print(e)
