import pandas as pd
import matplotlib.pyplot as plt


data = pd.read_csv("Scaling_Results1.csv")
for i in range(2,6):
    data = pd.concat([data, pd.read_csv("Scaling_Results"+str(i)+".csv")])
x = list(pd.Categorical(data['N_Nodes']).categories)
N_Nodes = x
data.sort_values(by=['N_Nodes', 'Degree', 'Read_Length'], inplace=True)
data_10 = data[data['Read_Length']==10]
data_50 = data[data['Read_Length']==50]
data_100 = data[data['Read_Length']==100]
data_150 = data[data['Read_Length']==150]
data_200 = data[data['Read_Length']==200]

i=0
f,axes = plt.subplots(2,2, figsize=(15,7))
f.suptitle('Alignment Time', fontsize=16)
for data_curr, q_len in zip([data_50, data_100, data_150, data_200],['50', '100', '150', '200']):
    plot=axes[i//2][i%2]
    plot.set_title('Query length = ' + q_len)
    plot.set_xlabel('Number of Nodes')
    plot.set_ylabel('Alignment Time [s]')
    #plot.set_ylim(0,0.65) #uncomment to set the same y axes for the 3 plots
    y1 = [data_curr[(data_curr['Degree']==1) & (data_curr['N_Nodes']==N)]['Align_Time(s)'].mean() for N in x]
    y2 = [data_curr[(data_curr['Degree']==2) & (data_curr['N_Nodes']==N)]['Align_Time(s)'].mean() for N in x]
    y3 = [data_curr[(data_curr['Degree']==3) & (data_curr['N_Nodes']==N)]['Align_Time(s)'].mean() for N in x]
    y4 = [data_curr[(data_curr['Degree']==4) & (data_curr['N_Nodes']==N)]['Align_Time(s)'].mean() for N in x]
    y5 = [data_curr[(data_curr['Degree']==5) & (data_curr['N_Nodes']==N)]['Align_Time(s)'].mean() for N in x]
    
    e1 = [data_curr[(data_curr['Degree']==1) & (data_curr['N_Nodes']==N)]['Align_Time(s)'].std() for N in x]
    e2 = [data_curr[(data_curr['Degree']==2) & (data_curr['N_Nodes']==N)]['Align_Time(s)'].std() for N in x]
    e3 = [data_curr[(data_curr['Degree']==3) & (data_curr['N_Nodes']==N)]['Align_Time(s)'].std() for N in x]
    e4 = [data_curr[(data_curr['Degree']==4) & (data_curr['N_Nodes']==N)]['Align_Time(s)'].std() for N in x]
    e5 = [data_curr[(data_curr['Degree']==5) & (data_curr['N_Nodes']==N)]['Align_Time(s)'].std() for N in x]
    real = [y1, y2, y3, y4, y5]
    errors = [e1, e2, e3, e4, e5]
    formats = [['-ro', '--rx'],['-go','--gx'],['-bo', '--bx'],['-ko','--kx'],['-co', '--cx']]

   
    t = []
    for degree in range(1,6):
        theory = 2000*(degree*int(q_len)+1)
        scaler = float(real[degree-1][1]/theory)
        tt = [a*(degree*int(q_len)+1)*scaler for a in x]
        t.append(tt)
    for val, err, teo, fmt, label in zip(real, errors, t, formats, range(1,6)):    
        plot.errorbar(x, val, yerr=err, fmt=fmt[0], label = str(label))#, x, y2, e2, '-go', x, y3, e3, '-bo', x, y4, e4, '-ko')#, x, y5, e5, '-co')#
        #plot.plot(x, teo, fmt[1], label = str(label) + '- theoretic') #, x, t[1], '--gx', x, t[2], '--bx', x, t[3], '--kx', x, t[4], '--cx')
    plot.legend(loc='best', title='Avg. Degree') #['1', '2', '3', '4', '5', '1 - theoretic', '2 - theoretic', '3 - theoretic', '4 - theoretic', '5 - theoretic'],
    i=i+1
    

plt.subplots_adjust(left=0.04, right=0.96, bottom=0.07, top=0.90, wspace=0.16, hspace=0.2)
plt.show()


x = list(pd.Categorical(data['Degree']).categories)
i=0
f,axes = plt.subplots(2,2, figsize=(15,7))
f.suptitle('Alignment Time', fontsize=16)
for data_curr, q_len in zip([data_50, data_100, data_150, data_200],['50', '100', '150', '200']):
    plot=axes[i//2][i%2]
    plot.set_title('Query length = ' + q_len)
    plot.set_xlabel('Average Degree')
    plot.set_ylabel('Alignment Time [s]')
    #plot.set_ylim(0,0.65) #uncomment to set the same y axes for the 3 plots
    y1 = list(data_curr[data_curr['N_Nodes']==1000]['Align_Time(s)'])
    y2 = list(data_curr[data_curr['N_Nodes']==2000]['Align_Time(s)'])
    y3 = list(data_curr[data_curr['N_Nodes']==4000]['Align_Time(s)'])
    y4 = list(data_curr[data_curr['N_Nodes']==8000]['Align_Time(s)'])
    y5 = list(data_curr[data_curr['N_Nodes']==16000]['Align_Time(s)'])
    y6 = list(data_curr[data_curr['N_Nodes']==32000]['Align_Time(s)'])
    y1 = [data_curr[(data_curr['Degree']==N) & (data_curr['N_Nodes']==1000)]['Align_Time(s)'].mean() for N in x]
    y2 = [data_curr[(data_curr['Degree']==N) & (data_curr['N_Nodes']==2000)]['Align_Time(s)'].mean() for N in x]
    y3 = [data_curr[(data_curr['Degree']==N) & (data_curr['N_Nodes']==4000)]['Align_Time(s)'].mean() for N in x]
    y4 = [data_curr[(data_curr['Degree']==N) & (data_curr['N_Nodes']==8000)]['Align_Time(s)'].mean() for N in x]
    y5 = [data_curr[(data_curr['Degree']==N) & (data_curr['N_Nodes']==16000)]['Align_Time(s)'].mean() for N in x]
    y6 = [data_curr[(data_curr['Degree']==N) & (data_curr['N_Nodes']==32000)]['Align_Time(s)'].mean() for N in x]

    e1 = [data_curr[(data_curr['Degree']==N) & (data_curr['N_Nodes']==1000)]['Align_Time(s)'].std() for N in x]
    e2 = [data_curr[(data_curr['Degree']==N) & (data_curr['N_Nodes']==2000)]['Align_Time(s)'].std() for N in x]
    e3 = [data_curr[(data_curr['Degree']==N) & (data_curr['N_Nodes']==4000)]['Align_Time(s)'].std() for N in x]
    e4 = [data_curr[(data_curr['Degree']==N) & (data_curr['N_Nodes']==8000)]['Align_Time(s)'].std() for N in x]
    e5 = [data_curr[(data_curr['Degree']==N) & (data_curr['N_Nodes']==16000)]['Align_Time(s)'].std() for N in x]
    e6 = [data_curr[(data_curr['Degree']==N) & (data_curr['N_Nodes']==32000)]['Align_Time(s)'].std() for N in x]
    real = [y1, y2, y3, y4, y5, y6]
    errors = [e1, e2, e3, e4, e5, e6]
    formats = [['-ro', '--rx'],['-go','--gx'],['-bo', '--bx'],['-ko','--kx'],['-co', '--cx'],['-mo', '--mx']]

   
    t = []
    for N,ii in zip(N_Nodes,range(6)):
        theory = N*(3*int(q_len)+1)
        scaler = float(real[ii][2]/theory)
        tt = [N*(a*int(q_len)+1)*scaler for a in x]
        t.append(tt)
    for val, err, teo, fmt, label in zip(real, errors, t, formats, N_Nodes):    
        plot.errorbar(x, val, yerr=err, fmt=fmt[0], label = str(label))#, x, y2, e2, '-go', x, y3, e3, '-bo', x, y4, e4, '-ko')#, x, y5, e5, '-co')#
        #plot.plot(x, teo, fmt[1], label = str(label) + '- theoretic') #, x, t[1], '--gx', x, t[2], '--bx', x, t[3], '--kx', x, t[4], '--cx')
    plot.legend(loc='best', title='# of Nodes') #['1', '2', '3', '4', '5', '1 - theoretic', '2 - theoretic', '3 - theoretic', '4 - theoretic', '5 - theoretic'],
    i = i+1

plt.subplots_adjust(left=0.04, right=0.96, bottom=0.07, top=0.90, wspace=0.16, hspace=0.2)
plt.show()

x = list(pd.Categorical(data['N_Nodes']).categories)
i=0
f,axes = plt.subplots(2,2, figsize=(15,7))
f.suptitle('Memory Usage', fontsize=16)
for data_curr, q_len in zip([data_50, data_100, data_150, data_200],['50', '100', '150', '200']):
    plot=axes[i//2][i%2]
    plot.set_title('Query length = ' + q_len)
    plot.set_xlabel('Number of Nodes')
    plot.set_ylabel('Memory Usage [MB]')
    #plot.set_ylim(0,0.65) #uncomment to set the same y axes for the 3 plots
    y1 = [data_curr[(data_curr['Degree']==1) & (data_curr['N_Nodes']==N)]['RAM_usage(bytes)'].mean()/(1024*1024) for N in x]
    y2 = [data_curr[(data_curr['Degree']==2) & (data_curr['N_Nodes']==N)]['RAM_usage(bytes)'].mean()/(1024*1024) for N in x]
    y3 = [data_curr[(data_curr['Degree']==3) & (data_curr['N_Nodes']==N)]['RAM_usage(bytes)'].mean()/(1024*1024) for N in x]
    y4 = [data_curr[(data_curr['Degree']==4) & (data_curr['N_Nodes']==N)]['RAM_usage(bytes)'].mean()/(1024*1024) for N in x]
    y5 = [data_curr[(data_curr['Degree']==5) & (data_curr['N_Nodes']==N)]['RAM_usage(bytes)'].mean()/(1024*1024) for N in x]
    
    e1 = [data_curr[(data_curr['Degree']==1) & (data_curr['N_Nodes']==N)]['RAM_usage(bytes)'].std()/(1024*1024) for N in x]
    e2 = [data_curr[(data_curr['Degree']==2) & (data_curr['N_Nodes']==N)]['RAM_usage(bytes)'].std()/(1024*1024) for N in x]
    e3 = [data_curr[(data_curr['Degree']==3) & (data_curr['N_Nodes']==N)]['RAM_usage(bytes)'].std()/(1024*1024) for N in x]
    e4 = [data_curr[(data_curr['Degree']==4) & (data_curr['N_Nodes']==N)]['RAM_usage(bytes)'].std()/(1024*1024) for N in x]
    e5 = [data_curr[(data_curr['Degree']==5) & (data_curr['N_Nodes']==N)]['RAM_usage(bytes)'].std()/(1024*1024) for N in x]
    real = [y1, y2, y3, y4, y5]
    errors = [e1, e2, e3, e4, e5]
    formats = [['-ro', '--rx'],['-go','--gx'],['-bo', '--bx'],['-ko','--kx'],['-co', '--cx']]
    for val, err, fmt, label in zip(real, errors, formats, range(1,6)):    
        plot.errorbar(x, val, yerr=err, fmt=fmt[0], label = str(label))#, x, y2, e2, '-go', x, y3, e3, '-bo', x, y4, e4, '-ko')#, x, y5, e5, '-co')#
        #plot.plot(x, teo, fmt[1], label = str(label) + '- theoretic') #, x, t[1], '--gx', x, t[2], '--bx', x, t[3], '--kx', x, t[4], '--cx')
    plot.legend(loc='best', title='Avg. Degree') #['1', '2', '3', '4', '5', '1 - theoretic', '2 - theoretic', '3 - theoretic', '4 - theoretic', '5 - theoretic'],
    i=i+1
    

plt.subplots_adjust(left=0.04, right=0.96, bottom=0.07, top=0.90, wspace=0.16, hspace=0.2)
plt.show()


x = list(pd.Categorical(data['Degree']).categories)
i=0
f,axes = plt.subplots(2,2, figsize=(15,7))
f.suptitle('Memory Usage', fontsize=16)
for data_curr, q_len in zip([data_50, data_100, data_150, data_200],['50', '100', '150', '200']):
    plot=axes[i//2][i%2]
    plot.set_title('Query length = ' + q_len)
    plot.set_xlabel('Average Degree')
    plot.set_ylabel('Memory Usage [MB]')
    #plot.set_ylim(0,0.65) #uncomment to set the same y axes for the 3 plots
    y1 = list(data_curr[data_curr['N_Nodes']==1000]['RAM_usage(bytes)'])
    y2 = list(data_curr[data_curr['N_Nodes']==2000]['RAM_usage(bytes)'])
    y3 = list(data_curr[data_curr['N_Nodes']==4000]['RAM_usage(bytes)'])
    y4 = list(data_curr[data_curr['N_Nodes']==8000]['RAM_usage(bytes)'])
    y5 = list(data_curr[data_curr['N_Nodes']==16000]['RAM_usage(bytes)'])
    y6 = list(data_curr[data_curr['N_Nodes']==32000]['RAM_usage(bytes)'])
    y1 = [data_curr[(data_curr['Degree']==N) & (data_curr['N_Nodes']==1000)]['RAM_usage(bytes)'].mean()/(1024*1024) for N in x]
    y2 = [data_curr[(data_curr['Degree']==N) & (data_curr['N_Nodes']==2000)]['RAM_usage(bytes)'].mean()/(1024*1024) for N in x]
    y3 = [data_curr[(data_curr['Degree']==N) & (data_curr['N_Nodes']==4000)]['RAM_usage(bytes)'].mean()/(1024*1024) for N in x]
    y4 = [data_curr[(data_curr['Degree']==N) & (data_curr['N_Nodes']==8000)]['RAM_usage(bytes)'].mean()/(1024*1024) for N in x]
    y5 = [data_curr[(data_curr['Degree']==N) & (data_curr['N_Nodes']==16000)]['RAM_usage(bytes)'].mean()/(1024*1024)for N in x]
    y6 = [data_curr[(data_curr['Degree']==N) & (data_curr['N_Nodes']==32000)]['RAM_usage(bytes)'].mean()/(1024*1024) for N in x]

    e1 = [data_curr[(data_curr['Degree']==N) & (data_curr['N_Nodes']==1000)]['RAM_usage(bytes)'].std()/(1024*1024) for N in x]
    e2 = [data_curr[(data_curr['Degree']==N) & (data_curr['N_Nodes']==2000)]['RAM_usage(bytes)'].std()/(1024*1024) for N in x]
    e3 = [data_curr[(data_curr['Degree']==N) & (data_curr['N_Nodes']==4000)]['RAM_usage(bytes)'].std()/(1024*1024) for N in x]
    e4 = [data_curr[(data_curr['Degree']==N) & (data_curr['N_Nodes']==8000)]['RAM_usage(bytes)'].std()/(1024*1024) for N in x]
    e5 = [data_curr[(data_curr['Degree']==N) & (data_curr['N_Nodes']==16000)]['RAM_usage(bytes)'].std()/(1024*1024) for N in x]
    e6 = [data_curr[(data_curr['Degree']==N) & (data_curr['N_Nodes']==32000)]['RAM_usage(bytes)'].std()/(1024*1024) for N in x]
    real = [y1, y2, y3, y4, y5, y6]
    errors = [e1, e2, e3, e4, e5, e6]
    formats = [['-ro', '--rx'],['-go','--gx'],['-bo', '--bx'],['-ko','--kx'],['-co', '--cx'],['-mo', '--mx']]

   
    t = []
    for N,ii in zip(N_Nodes,range(6)):
        theory = N*(3*int(q_len)+1)
        scaler = float(real[ii][2]/theory)
        tt = [N*(a*int(q_len)+1)*scaler for a in x]
        t.append(tt)
    for val, err, fmt, label in zip(real, errors, formats, N_Nodes):    
        plot.errorbar(x, val, yerr=err, fmt=fmt[0], label = str(label))#, x, y2, e2, '-go', x, y3, e3, '-bo', x, y4, e4, '-ko')#, x, y5, e5, '-co')#
        #plot.plot(x, teo, fmt[1], label = str(label) + '- theoretic') #, x, t[1], '--gx', x, t[2], '--bx', x, t[3], '--kx', x, t[4], '--cx')
    plot.legend(loc='best', title='# of Nodes') #['1', '2', '3', '4', '5', '1 - theoretic', '2 - theoretic', '3 - theoretic', '4 - theoretic', '5 - theoretic'],
    i = i+1

plt.subplots_adjust(left=0.04, right=0.96, bottom=0.07, top=0.90, wspace=0.16, hspace=0.2)
plt.show()
