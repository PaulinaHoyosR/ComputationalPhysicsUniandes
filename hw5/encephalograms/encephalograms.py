import numpy as np
from numpy import *
import scipy as scp
from scipy  import *
from scipy.fftpack import fft, fftfreq
import matplotlib as mp
import matplotlib.pyplot as plt



def get_es_size(filename):
    """
    Counts lines to get the size of electrode signals arrays.
    
    Input: filename
    Output: size of each electrode signal (integer)
    """

    with open(filename) as file:
        size = sum(1 for line in file)

    return size
   

 
def load_data(filename, size_es):
    """
    Loads encephalograms data from a plain text file.
    
    Input: filename.
    Output: numpy array with all the data.
    """
    
    #Declare size of the matrix. First index indicates the electrode signal. 
    esignal = [[0 for x in xrange(size_es)] for x in xrange(24)] 
    
    #Assign values to the esignal matrix
    for i in range(0,24):
        esignal[i] = loadtxt(filename, unpack=True, usecols=[i])

    return esignal



def apply_fft(esignal, size_es, delta_time):
    """
    Applies fast fourier transform pyhton routines to input data.
    
    Input: 
    -numpy array  with 24 arrays with data of each electrode signal.
    -The size of the 24 arrays
    -The spacing in time for data

    Output: three numpy arrays. 
    -fft_amplitudes(normalized and non-normalized):numpy array with 24  numpy complex arrays, each one indicate fourier amplitudes for each electrode signal.
    -fft_freq: numpy array with 24  numpy arrays, each one indicates fourier frecuencies for each electrode signal.
    """

    fft_amplitudes_nn = [[0 for x in xrange(size_es)] for x in xrange(24)]
    fft_amplitudes_nn_shifted = [[0 for x in xrange(size_es)] for x in xrange(24)]
    
    fft_amplitudes = [[0 for x in xrange(size_es)] for x in xrange(24)]
    fft_amplitudes_shifted = [[0 for x in xrange(size_es)] for x in xrange(24)]

    fft_frequencies = [[0 for x in xrange(size_es)] for x in xrange(24)]
    fft_frequencies_shifted = [[0 for x in xrange(size_es)] for x in xrange(24)]


    for i in range(0,24):
       
         fft_amplitudes_nn[i] = fft(esignal[i]) #FFT non-normalized. Array with complex numbers. 
         fft_amplitudes_nn_shifted[i] = np.fft.fftshift(fft_amplitudes_nn[i])

         fft_amplitudes[i] = fft(esignal[i])/size_es #FFT normalized. Array with complex numbers.
         fft_amplitudes_shifted[i] = np.fft.fftshift(fft_amplitudes[i]) 
         
         fft_frequencies[i] = fftfreq(size_es, delta_time)
         fft_frequencies_shifted[i] = np.fft.fftshift(fft_frequencies[i])

    return fft_amplitudes_nn_shifted,fft_amplitudes_shifted,fft_frequencies_shifted



def get_power_spectrum(fft_amplitudes, fft_frequencies, size_es):
    """
    Uses the 24 fft_amplitudes and fft_frequencies arrays to compute the power spectrum for the 24 electrode signals.

    Input: 2 numpy arrays with 24 arrays inside for each electrode signal.
    -fft_amplitudes: numpy complex array with fourier amplitudes normalized.
    -fft_freq: numpy array with frecuencies for each signal.

    Output: numpy array with 24 arrays that contain the power spectrum for each signal.
    """
    
    fft_amplitudes_squared= [[0 for x in xrange(size_es)] for x in xrange(24)]
    half_size_es = int(size_es/2.0)
    fft_amplitudes_squared_positive = [[0 for x in xrange(half_size_es)] for x in xrange(24)]
    fft_frequencies_positive = [[0 for x in xrange(half_size_es)] for x in xrange(24)]

    for i in range(0,24):
        fft_amplitudes_squared[i] = 2.0*np.absolute(fft_amplitudes[i])
        fft_amplitudes_squared_positive[i]= fft_amplitudes_squared[i][half_size_es:]
        fft_frequencies_positive[i]=fft_frequencies[i][half_size_es:]

    return fft_amplitudes_squared_positive, fft_frequencies_positive



def clean_data(fft_amplitudes_nn):
    """
    Sets to cero the values of the transform that are different from the 10 highest ones. This action is performed for the 24 electrode signals.

    Input: numpy array with 24 arrays inside, each one contains fourier amplitudes non-normalized.
    Output: numpy array with 24 arrays inside, each one contains filtered fourier amplitudes non-normalized.
    """

    for i in range(0,24):
        
        #Organize fft_amplitudes_nn[i] array in descending order
        sorted(fft_amplitudes_nn[i], reverse=True)

        #Set to cero the values of fft_amplitudes_nn[i] 
        fft_amplitudes_nn[i][10:] = 0

    return fft_amplitudes_nn



def apply_ifft(fft_amplitudes_nn,size_es):
    """
    Applies inverse fast fourier transform pyhton routines to input data.
    
    Input: numpy array with 24 arrays inside, each one contains contains fourier amplitudes non-normalized.
    Output: numpy arrays with 24 numpy complex arrays inside, each one contains the inverse fourier transform for each electrode signal.
    """
    
    clean_esignal = [[0 for x in xrange(size_es)] for x in xrange(24)]

    for i in range(0,24):
        clean_esignal[i]=ifft(fft_amplitudes_nn[i])

    return np.real(clean_esignal)
    
    

def calculate_chi_square(esignal, clean_esignal, size_es):
    """
    Calculates chi_square for the 24 pairs of electrode signals (original and clean).

    Input: 2 numpy arrays with 24 arrays inside.
    -esignal= original data for each electrode signal.
    -clean_esignal = filtered data for each electrode signal.

    Output: 1 numpy array with 24 numbers inside, each number indicates chi-square.
    """
    
    #Initialize array with zeros for the sumatory
    chi_square = [0.0]*24
    
    #Loop to acumulate values for chi_square
    for i in range(0,24):
        for j in range(0, size_es):
            chi_square[i] = chi_square[i] + (esignal[i][j]-clean_esignal[i][j])**2
        chi_square[i] = chi_square[i]/size_es

    return np.real(chi_square)



def make_plot(x,y,name,xlabel,ylabel):
    """
    Plots y vs x

    Input: 
    - x and y data. Both must have same size.
    - Name to save the figure.
    - xlabel and ylabel to make plots prettier and better.

    Output: Nothing.
    """
    plt.plot(x,y, color='g')
    plt.xlabel(xlabel)
    plt.ylabel(ylabel)
    plt.savefig(name+'.png')
    plt.clf()

    plt.plot(x,y, color='g')
    plt.yscale('log')
    plt.xlabel(xlabel)
    plt.ylabel(ylabel)
    plt.savefig(name+'_log_scale.png')
    plt.clf()



def make_plot_yalone(y,name,xlabel,ylabel, color):
    """
    Plots y.

    Input: 
    - y data
    - Name to save the figure.
    - xlabel and ylabel to make plots prettier and better.

    Output: Nothing.
    """
    plt.plot(y, color=color)
    plt.xlabel(xlabel)
    plt.ylabel(ylabel)
    plt.savefig(name+'.png')
    plt.clf()



def main():

    #Defines the input file
    input_filename = 'sampled+ma0844az_1-1+_data.txt'

    #Gets size of each electrode signal array
    size_es = get_es_size(input_filename)
    
    #Loads the data
    esignal = load_data(input_filename, size_es)

    #Applies FFT routineslean_esignal[i
    fft_amplitudes_nn, fft_amplitudes, fft_frequencies = apply_fft(esignal, size_es, 1)

    #Computes the power spectrum
    fft_amplitudes_ps, fft_frequencies_ps = get_power_spectrum(fft_amplitudes, fft_frequencies, size_es)

    #Filters data
    clean_fft_amplitudes_nn = clean_data(fft_amplitudes_nn)

    #Applies inverse FFT routines
    clean_esignal = apply_ifft(clean_fft_amplitudes_nn,size_es)

    #Make power spectrum plots
    for i in range(0,24):
        make_plot(fft_frequencies_ps[i], fft_amplitudes_ps[i], 'power_spectrum'+str(i), 'Frequency (1/min)', 'Amplitude (No ' +str(i)+')')
    
    #Make original electrode signal plots
    for i in range(0,24):
        make_plot_yalone(esignal[i], 'Original_esignal'+str(i), 'Time (min)', 'Electrode Signal No '+str(i), color='b')

    #Make modified electrode signal plots
    for i in range(0,24):
        make_plot_yalone(clean_esignal[i], 'Modified_esignal'+str(i), 'Time (min)', 'Electrode Signal No '+str(i), color='r')

    #Get  chi_square data
    chi_square = calculate_chi_square(esignal, clean_esignal, size_es)

    #Write chi_square data in a file
    new_file =  open('chi_square.dat', 'w')

    for i in range(0,24):
        new_file.write(str(i)+':  '+str(chi_square[i])+'\n')

   
if __name__ == "__main__":
    main()
