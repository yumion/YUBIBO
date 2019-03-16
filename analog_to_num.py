def convert_to_region(thumb):
    num = 0
    # 指のどの関節にいるか検知
    if thumb > 2000:
        # 接触なし
        num = 15
    elif thumb > 1850:
        # space
        num = 12
    elif thumb > 1750:
        # delete
        num = 13
    elif thumb > 1650:
        # enter
        num = 14
    elif thumb > 1550:
        # あ
        num = 0
    elif thumb > 1470:
        # か
        num = 1
    elif thumb > 1350:
        # さ
        num = 2
    elif thumb > 1250:
        # た
        num = 3
    elif thumb > 1100:
        # な
        num = 4
    elif thumb > 1000:
        # は
        num = 5
    elif thumb > 800:
        # ま
        num = 6
    elif thumb > 700:
        # や
        num = 7
    elif thumb > 500:
        # ら
        num = 8
    elif thumb > 300:
        # 濁点、半濁点、小文字
        num = 9
    elif thumb > 100:
        # わ
        num = 10
    else:
        # Enter
        num = 11
    return num
