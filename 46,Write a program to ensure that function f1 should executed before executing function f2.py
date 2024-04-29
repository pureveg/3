import threading

# Semaphore initialization
semaphore = threading.Semaphore(0)

def get_username():
    username = input("Enter your username: ")
    print("Username:", username)
    # Release semaphore after username is obtained
    semaphore.release()

def get_password():
    # Wait for semaphore to be released before entering password
    semaphore.acquire()
    password = input("Enter your password: ")
    print("Password:", password)

# Create threads for username and password
thread_username = threading.Thread(target=get_username)
thread_password = threading.Thread(target=get_password)

# Start the threads
thread_username.start()
thread_password.start()

# Join the threads to ensure they finish execution before the program exits
thread_username.join()
thread_password.join()




