import numpy as np
import scipy as scp
from scipy.interpolate import *
from scipy.fftpack import *
from scipy.fftpack import fftfreq
import matplotlib.pyplot as plt

"""
Skeleton of code with all the functions and steps to process sunspots data
Authors: Mateo Restrepo Ayala (201226523) and Paulina Hoyos Restrepo (201210746)
Creation date: Tuesday, October 8 2013
Due date: Thursday, October 10 2013
"""


def load_data(filename):
    """
    Loads sunspots data from a plain text file.
    
    Input: filename.
    Output: numpy array with all the data.
    """
    
    #Load data as 3 numpy arrays from the input file. These arrays will be needed to fill the output array.
    year= np.loadtxt(filename, unpack=True, usecols=[0])
    month = np.loadtxt(filename, unpack=True, usecols=[1])
    number_sunspots = np.loadtxt(filename, unpack=True, usecols=[3])

    #Get number from wich there are no more months without measurements
    number_sunspots_backwards = number_sunspots[::-1]
    
    for i in range(0,len(number_sunspots_backwards)):
        if number_sunspots_backwards[i]==-99.0:
            number_down_up = i
            break

    number_up_down = len(number_sunspots_backwards) - i 

    #New arrays from number_up-down
    year_cut = [0.0]*number_down_up
    month_cut = [0.0]*number_down_up
    number_sunspots_cut = [0.0]*number_down_up
    
    year_cut = year[number_up_down:]
    month_cut = month[number_up_down:]
    number_sunspots_cut = number_sunspots[number_up_down:]

    #Values needed for further calculations.
    size = len(year_cut)
    first_year = year_cut[0]
    last_year = year_cut[-1]

    #Initialize the output arrays. 
    output_month = [0.0]*size
    output_sunspots = [0.0]*size

    #Loop to assign values from input data to output array.
    for i in range(0, size):
        month_number = int((year_cut[i]-first_year)*12 + month_cut[i])
        output_month[i] = month_number
        output_sunspots[i] = number_sunspots_cut[i]
      
    return output_month, output_sunspots


def constant_interpolate(month_array, sunspots_array):
    """
    Makes a constant interpolation for input data.

    Input: numpy array with data not evenly spaced in time.
    Output: numpy array with data evenly spaced in time.
    """

    #Prepare function to interpolate data
    f = interp1d(month_array,sunspots_array,kind='nearest')

    #Get new array to fill in
    size = (1995-1796)*12

    new_month_array = [0.0]*size
    new_sunspots_array = [0.0]*size

    for i in range(0,size):
        new_month_array[i] = i+3

    #Use interpolation function to get number_sunspots values
    for i in range(0,size):
        new_sunspots_array[i] = f(new_month_array[i])
        
    return new_sunspots_array


def linear_interpolate(month_array, sunspots_array):
    """
    Makes a linear interpolation for input data.
    
    Input: numpy array with data not evenly spaced in time.
    Output: numpy array with data evenly spaced in time.
    """
    #Prepare function to interpolate data
    f= interp1d(month_array,sunspots_array,kind='linear')

    #Get new array to fill in
    size = (1995-1796)*12

    new_month_array = [0.0]*size
    new_sunspots_array = [0.0]*size

    for i in range(0,size):
        new_month_array[i] = i+3

    #Use interpolation function to get number_sunspots values
    for i in range(0,size):
        new_sunspots_array[i] = f(new_month_array[i])
    return new_sunspots_array




def cubic_interpolate(month_array, sunspots_array):
    """
    Makes a cubic interpolation for input data.
    
    Input: numpy array  with data not evenly spaced in time.
    Output: numpy array with data evenly spaced in time.
    """  
    #Prepare function to interpolate data
    f = interp1d(month_array,sunspots_array,kind='cubic')

    #Get new array to fill in
    size = (1995-1796)*12

    new_month_array = [0.0]*size
    new_sunspots_array = [0.0]*size

    for i in range(0,size):
        new_month_array[i] = i+3

    #Use interpolation function to get number_sunspots values
    for i in range(0,size):
        new_sunspots_array[i] = f(new_month_array[i])

    return new_sunspots_array




def apply_fft(sunspots_array, delta_time):
    """
    Applies fast fourier transform pyhton routines to input data.
    
    Input: numpy array with number of sunspots per month evenly spaced in time.
    Output: two numpy arrays. 
    -fft_amplitudes: numpy complex arrat with fourier amplitudes.
    -fft_freq: numpy arrat with frecuencies for each signal.
    """

    fft_amplitudes = fft(sunspots_array) #FFT non-normalized

    number_points = len(sunspots_array)
    fft_frequencies = fftfreq(number_points, delta_time)

    return fft_amplitudes,fft_frequencies


def get_power_spectrum(fft_amplitudes, fft_frequencies):
    """
    Uses the fft_amplitudes and fft_frequencies arrays to compute the power spectrum.

    Input: 2 numpy arrays.
    -fft_amplitudes: numpy complex arrat with fourier amplitudes.
    -fft_freq: numpy arrat with frecuencies for each signal
    Output: numpy array with the power spectrum for each signal.
    """
    fft_amplitudes_squared = np.absolute(fft_amplitudes)
    size = len(fft_amplitudes_squared)
    size_half = int(size/2.0)
    fft_amplitudes_squared_half = 2.0 * fft_amplitudes_squared[:size_half]
    fft_frequencies_half = fft_frequencies[:size_half]
    return fft_amplitudes_squared_half, fft_frequencies_half
   
   

def clean_data(fft_amplitudes,fft_frequencies):
     """
    Sets to cero the values of the transform that are outside of the period limits.
    
    Input: numpy array with fourier amplitudes, numpy array with fourier frequencies, inferior period limit in terms of months(integer), superior period limit (integer).
    Output: numpy array.
    """

    #Calculate limits in terms of frequency
     inferior_limit = 1.0/(20.0*12.0)
     superior_limit = 1.0/(2.0*12.0)
     
     num = fft_amplitudes[fft_frequencies==0]

    #Sets to zero the values of fft_array outside limits:
     fft_amplitudes[np.absolute(fft_frequencies)<inferior_limit]=0
     fft_amplitudes[np.absolute(fft_frequencies)>superior_limit]=0
     fft_amplitudes[fft_frequencies==0]=num

     return fft_amplitudes


def apply_ifft(fft_amplitudes):
    """
    Applies inverse fast fourier transform pyhton routines to input data.
    
    Input: numpy complex array with fourier amplitudes. 
    Output: numpy complex array with the inverse fourier transform.
    """
    inverse_fft_amplitudes = ifft(fft_amplitudes)

    return inverse_fft_amplitudes


def make_plot(x, y, name, xlabel, ylabel):
    """
    Plots y vs x.

    Input: x data, y data
    Output: Nothing
    """
    plt.plot(x,y)
    plt.yscale('log')
    plt.xlabel(xlabel)
    plt.ylabel(ylabel)
    plt.savefig(name+'_log_scale.png')    
    plt.clf()

    plt.plot(x,y)
    plt.xlabel(xlabel)
    plt.ylabel(ylabel)
    plt.savefig(name+'.png')    
    plt.clf()


def calculate_period(fft_amplitudes, fft_frequencies):
    """
    Calcultes period for the solar cycle.

    Input: array with clean number of sunspots data.
    Output: Number of months between 2 solar maximun activity. (float)
    """
    #Calculate period
    fft_amplitudes[fft_frequencies==0]=0
    greatest_amplitude = fft_amplitudes.max()
    dominant_frequency = fft_frequencies[fft_amplitudes == greatest_amplitude]
    period_months = 1/dominant_frequency
    period_years = period_months/12.0
    return period_years

def main():

    #Defines the input file
    input_filename = 'sparse_sample_monthrg.dat'

    #Loads the data
    month_data, sunspots_data = load_data(input_filename)

    #Applies the three types of interpolation
    data_constant = constant_interpolate(month_data, sunspots_data)
    data_linear = linear_interpolate(month_data, sunspots_data)
    data_cubic = cubic_interpolate(month_data, sunspots_data)

    #Applies FFT routines 
    fft_amplitudes_constant, fft_frequencies_constant = apply_fft(data_constant,1)
    fft_amplitudes_linear, fft_frequencies_linear = apply_fft(data_linear,1)
    fft_amplitudes_cubic, fft_frequencies_cubic = apply_fft(data_cubic,1)

    #Computes the power spectrum 
    fft_amplitudes_ps_constant, fft_frequencies_ps_constant = get_power_spectrum(fft_amplitudes_constant,fft_frequencies_constant)
    fft_amplitudes_ps_linear, fft_frequencies_ps_linear = get_power_spectrum(fft_amplitudes_linear, fft_frequencies_linear)
    fft_amplitudes_ps_cubic, fft_frequencies_ps_cubic = get_power_spectrum(fft_amplitudes_cubic, fft_frequencies_cubic)

    #Cleans data
    clean_fft_amplitudes_constant = clean_data(fft_amplitudes_constant, fft_frequencies_constant)
    clean_fft_amplitudes_linear = clean_data(fft_amplitudes_linear, fft_frequencies_linear)
    clean_fft_amplitudes_cubic = clean_data(fft_amplitudes_cubic, fft_frequencies_cubic)

    #Apply inverse FFT routines
    clean_data_constant = apply_ifft(clean_fft_amplitudes_constant)
    clean_data_linear = apply_ifft(clean_fft_amplitudes_linear)
    clean_data_cubic = apply_ifft(clean_fft_amplitudes_cubic)

    #Calculate period for solar cycle
    period_constant = calculate_period(clean_fft_amplitudes_constant, fft_frequencies_constant )
    period_linear = calculate_period(clean_fft_amplitudes_linear, fft_frequencies_linear)
    period_cubic = calculate_period(clean_fft_amplitudes_cubic, fft_frequencies_cubic)

    mean_period = (period_constant + period_linear)/(2.0)
    print mean_period

    #Plot the 3 power spectrums  
    make_plot(fft_frequencies_ps_constant, fft_amplitudes_ps_constant, 'power_spectrum_constant', 'Frequency (1/month)', ' Amplitude')
    make_plot(fft_frequencies_ps_linear, fft_amplitudes_ps_linear, 'power_spectrum_linear', ' Frequency (1/month)', ' Amplitude')
    make_plot(fft_frequencies_ps_cubic, fft_amplitudes_ps_cubic, 'power_spectrum_cubic', ' Frequency (1/month)', 'Amplitude')


    #Plot Original and modified data in the same figure

    new_month_data = [0.0]*len(month_data)
    for i  in range(0, len(month_data)):
        new_month_data[i] = month_data[i]/12.0
   
    x_data_clean = [0.0]*len(clean_data_cubic)
    for i in range(0,len(clean_data_cubic)):
        x_data_clean[i]= i/12.0

    plt.plot(new_month_data, sunspots_data)
    plt.plot(x_data_clean,np.absolute(np.real(clean_data_constant)), linewidth=0.5)
    plt.yscale('log')
    plt.xlabel('time (years)')
    plt.ylabel('Number of sunspots')
    plt.savefig('sunspots_data_constant_log_scale.png')
    plt.clf()
    

    plt.plot(new_month_data, sunspots_data)
    plt.plot(x_data_clean, np.absolute(np.real(clean_data_linear)))
    plt.yscale('log')
    plt.xlabel('time (years)')
    plt.ylabel('Number of sunspots')
    plt.savefig('sunspots_data_linear_log_scale.png')
    plt.clf()


    plt.plot(new_month_data, sunspots_data)
    plt.plot(x_data_clean, np.absolute(np.real(clean_data_cubic)))
    plt.yscale('log')
    plt.xlabel('time (years)')
    plt.ylabel('Number of sunspots')
    plt.savefig('sunspots_data_cubic_log_scale.png')
    plt.clf()

    plt.plot(new_month_data, sunspots_data)
    plt.plot(x_data_clean,np.absolute(np.real(clean_data_constant)), linewidth=0.5)
    plt.xlabel('time (years)')
    plt.ylabel('Number of sunspots')
    plt.savefig('sunspots_data_constant.png')
    plt.clf()
    

    plt.plot(new_month_data, sunspots_data)
    plt.plot(x_data_clean, np.absolute(np.real(clean_data_linear)))
    plt.xlabel('time (years)')
    plt.ylabel('Number of sunspots')
    plt.savefig('sunspots_data_linear.png')
    plt.clf()


    plt.plot(new_month_data, sunspots_data)
    plt.plot(x_data_clean, np.absolute(np.real(clean_data_cubic)))
    plt.xlabel('time (years)')
    plt.ylabel('Number of sunspots')
    plt.savefig('sunspots_data_cubic.png')
    plt.clf()

  
if __name__ == "__main__":
    main()
