import matplotlib.pyplot as plt
import numpy as np
from matplotlib.ticker import FormatStrFormatter
import pandas as pd
import math
from matplotlib.ticker import StrMethodFormatter

def main():

    # COMPRESSED AUDIO

    #LEFT CHANNEL
    data = pd.read_csv('hists/leftChannelResiduals.txt', sep=',',header=None, index_col =0)

    data.plot(kind='bar')
    plt.ylabel('Number of Frequencies')
    plt.gca().set_xticks(plt.gca().get_xticks()[::10])
    plt.xlabel('Frequency')
    plt.title('Compressed Left Channel Histogram')

    
    plt.savefig('images/CompressedleftHist.png',bbox_inches="tight")
    
    # RIGHT CHANNEL
    data = pd.read_csv('hists/rightChannelResiduals.txt', sep=',',header=None, index_col =0)

    data.plot(kind='bar')
    plt.ylabel('Number of Frequencies')
    plt.gca().set_xticks(plt.gca().get_xticks()[::10])
    plt.xlabel('Frequency')
    plt.title('Compressed Right Channel Histogram')

    
    plt.savefig('images/CompressedrightHist.png',bbox_inches="tight")


    ## ORIGINAL AUDIO


    #LEFT CHANNEL
    data = pd.read_csv('hists/OriginalLeftChannelResiduals.txt', sep=',',header=None, index_col =0)

    data.plot(kind='bar')
    plt.ylabel('Number of Frequencies')
    plt.gca().set_xticks(plt.gca().get_xticks()[::10])
    plt.xlabel('Frequency')
    plt.title('Original Left Channel Histogram')

    
    plt.savefig('images/OriginalLeftHist.png',bbox_inches="tight")
    
    # RIGHT CHANNEL
    data = pd.read_csv('hists/OriginalRightChannelResiduals.txt', sep=',',header=None, index_col =0)

    data.plot(kind='bar')
    plt.ylabel('Number of Frequencies')
    plt.gca().set_xticks(plt.gca().get_xticks()[::10])
    plt.xlabel('Frequency')
    plt.title('Original Right Channel Histogram')

    
    plt.savefig('images/OriginalRightHist.png',bbox_inches="tight")


if __name__== "__main__":
    main()
