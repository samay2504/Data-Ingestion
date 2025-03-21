from typing import Dict


def authenticate_creds(config: Dict, username: str, password: str) -> bool:
    usernames = config["credentials"]["usernames"]
    if username in usernames and password == config["credentials"]["usernames"][username]["password"]:
        print("Login Successfull")
        return True, config["credentials"]["usernames"][username]
    else:
        print("Invalid Credentials")
        return False, None