import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
import seaborn as sns              
import matplotlib.ticker as tkr
import matplotlib.gridspec as gridspec
from matplotlib.patches import Patch
import os
import matplotlib.lines as lines
import matplotlib.ticker as ticker
from plot_utils import *

PALETTE = [COLORS["peach2"], COLORS["g1"]]
PALETTE_B = [COLORS["b3"], COLORS["b3"]]
PALETTE_GW = [COLORS[r] for r in ["gw3","gw2","gw1"]]
HATCHES = ['', '/'*4, '\\'*4]

data = pd.read_csv("KGE_Benchmark_Results_complete.csv", sep=';')
data['Configuration'] = ['CPU']*len(data)
data['Peak_RAM'] = data['Peak_RAM']/1000000.0
data['Peak_RAM_load_graph'] = data['Peak_RAM_load_graph']/1000000.0
data['Peak_RAM'] = data['Peak_RAM']-data['Peak_RAM_load_graph']
CPU = (data['Use_Vector'] == 0) & (data['Use_GPU'] == 0)
GPU = data['Use_GPU'] == 1
VECT = data['Use_Vector'] == 1
data.loc[GPU,'Configuration'] = ['GPU']*len(data[GPU])
data.loc[VECT,'Configuration'] = ['VECT']*len(data[VECT])

#print(data)
# print(dataCPU)
# print(dataVECT)
# print(dataGPU)

# sns.set_theme(style="whitegrid")
sns.set_style("whitegrid", {"ytick.left": True})
plt.rcParams["font.family"] = ["serif"]
plt.rcParams["font.size"] = 12
plt.rcParams['hatch.linewidth'] = 0.6
plt.rcParams['axes.labelpad'] = 5 
plt.rcParams['pdf.fonttype'] = 42
plt.rcParams['ps.fonttype'] = 42

conf = ['CPU','VECT','GPU']
ylabels = {'Wall_train':"Training Time [s]", 'CPU_train':"CPU Training Time", "Peak_RAM":"RAM occupation [MB]", "Peak_RAM_load_graph":"RAM occupation [MB]"}
ylims = {'Wall_train': [(0,10000),(0,10000),(0,80000)], 'Peak_RAM':[(0,500)]*3, 'CPU_train':[(0,140000),(0,140000),(0,1800000)], 'Peak_RAM_load_graph':[(0,500)]*3}

for var in ["Wall_train","CPU_train","Peak_RAM","Peak_RAM_load_graph"]: 
    g = sns.catplot(data=data, kind='bar', ci=99, x="N_threads",
    y=var, hue='Configuration', hue_order=conf, col='Graph', 
    col_order=['wn18', 'wn18rr', 'fb15k', 'fb15k-237', 'yago3-10'],
    row='Model', row_order=['distmult', 'transe', 'convkb'], alpha=1, 
    palette=PALETTE_GW, height=2.5, aspect=1, legend_out=False, 
    sharey=False, sharex=False, margin_titles=True)
    g.set_axis_labels("Number of CPU threads", ylabels[var])
    #g.despine(left=True)
    #  .set_titles("{col_name}")
    # .set_yticklabels(list(range(100,1000,100))+list(range(1000,10000,1000))+list(range(10000, 75000, 10000)))
    #  

    for i,axes in enumerate(g.axes):  
        for ii,ax in enumerate(axes):
            ax.set(ylim=ylims[var][i])
            plt.sca(axes[ii])
        #if ii!=0:
            a = list(range(0, ylims[var][i][1]+1,(ylims[var][i][1]+1)//4))
            print(a)
            plt.yticks(a)
            if ii!=0:
                plt.yticks(a, ['']*5)
            g.set_axis_labels("Number of CPU threads", ylabels[var])
            for j, bar in enumerate(ax.patches):
                bar.set_hatch(HATCHES[(j%15)//5])
                bar.set_edgecolor('k')
                
            # for j, bar in enumerate([p for p in ax.patches if not pd.isna(p)]):
            #     bar.set_hatch(HATCHES[j // len(axes)])
    #     ax.yaxis.set_minor_locator(tkr.LogLocator(base=10, subs='all'))
    #     ax.yaxis.set_minor_formatter(tkr.NullFormatter())
    # if var == 'Wall_train':
    #     g.set(yscale='log')
        
    # Add legend;
    # g.legend.remove()  # Remove the existing legend again;
    custom_lines = [Patch(facecolor=PALETTE_GW[0], hatch=HATCHES[0], edgecolor="k", label=conf[0]),
                    Patch(facecolor=PALETTE_GW[1], hatch=HATCHES[1], edgecolor="k", label=conf[1]),
                    Patch(facecolor=PALETTE_GW[2], hatch=HATCHES[2], edgecolor="k", label=conf[2])] 
                    
    legend_data = {a:b for a,b in zip(conf,custom_lines)}
    g.add_legend(legend_data, conf, loc="upper center", bbox_to_anchor=(0.505, 0.9), fontsize=10, ncol=1, handletextpad=0.2, columnspacing=0.4, fancybox=True)
    g.legend.set_title("HW Configuration")
    # leg._legend_box.align = "left"
    g.legend.get_frame().set_facecolor('white')
    plt.subplots_adjust(left=0.07, bottom=0.065, right=0.98, top=0.96, hspace=0.2, wspace=0.14)
    plt.savefig(f"Total{var}.pdf")
    plt.show()

