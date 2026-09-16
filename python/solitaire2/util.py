def parseable_as_int(arg: str):
    try:
        result = int(arg)
        return True
    except:
        return False
