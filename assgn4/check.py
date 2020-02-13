import time 

curr = time.time()
result = 3200001%1024
end = time.time()
exec_time = end - curr

curr = time.time()
result = 3200001>>10
end = time.time()

exec_time_shift = end - curr

print(exec_time)
print(exec_time_shift)