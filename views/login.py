import streamlit as st
from yaml.loader import SafeLoader
from utils.authenticate import authenticate_creds
import yaml

with open('secrets.yaml', 'r', encoding='utf-8') as file:
    config = yaml.load(file, Loader=SafeLoader)

st.title("Login Page")

st.markdown("### Enter Your Credentials")
username = st.text_input("Username")
password = st.text_input("Password", type="password")
submit = st.button("Submit")

if submit and authenticate_creds(config, username, password):
    st.session_state.logged = True
    st.success("Login Successful")
    st.session_state.role = config["credentials"]["usernames"][username]["role"]
    st.session_state.config_user = config["credentials"]["usernames"][username]
    st.rerun()
elif submit and not authenticate_creds(config, username, password):
    st.session_state.logged = False
    st.error("Login Failed")
    st.rerun()
else:
    pass
