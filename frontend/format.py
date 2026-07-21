MAGENTA = PURPLE = VIOLET   = '\033[95m'
BLUE = CERULEAN             = '\033[94m'
CYAN                        = '\033[96m'
GREEN = OKAY = OK           = '\033[92m'
YELLOW = WARNING            = '\033[93m'
RED = ERROR = FAIL          = '\033[91m'

CLEAR                       = '\033[0m'
BOLD                        = '\033[1m'
UNDERLINE                   = '\033[4m'

def temp(msg):
    print(YELLOW + msg + CLEAR, end="\r")

def success(msg):
    print(OKAY + msg + CLEAR)

def throw(err):
    raise Exception(ERROR + err)