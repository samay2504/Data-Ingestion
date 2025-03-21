import streamlit as st

if "logged" not in st.session_state:
    st.session_state.logged = False
    
def logout():
    if st.button("Log Out"):
        st.session_state.logged = False
        st.rerun()

login_page = st.Page("views/login.py", title="Login")
logout_page = st.Page(logout, title="Logout", icon=":material/logout:")
admin_page = st.Page("views/admin.py", title="Admin")
home_page = st.Page("views/home.py", title="Home")
bookings_page = st.Page("views/bookings.py", title="Booking")
payment_page = st.Page("views/payment.py", title="Payment")
profile_page = st.Page("views/profile.py", title="Profile")

if st.session_state.logged:
    if st.session_state.role == "user":
        pg = st.navigation(
            {
                "Account": [profile_page, logout_page],
                "Utilities": [bookings_page, payment_page]
            }
        )
    elif st.session_state.role == "admin":
        pg = st.navigation(
            {
                "Admin": [admin_page, profile_page, logout_page]
            }
        )
else:
    pg = st.navigation([login_page])

pg.run()
