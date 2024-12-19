import pandas as pd
import matplotlib.pyplot as plt
import numpy as np
import scipy.io.wavfile as wavfile 

def create_wav_file(samplingRate,voltages,fileName):
    # Normalize voltage to fit within -32767 to 32767 (16 bit int)
    minVoltage = np.min(np.abs(voltages))
    maxVoltage = np.max(np.abs(voltages))
    meanVoltage = (maxVoltage - minVoltage) / 2
    voltages = np.array(voltages)
    
    normalizedVoltage = (voltages-meanVoltage) / (maxVoltage-meanVoltage) * 32767

    # Write audio samples to a WAV file
    wavfile.write(fileName, int(samplingRate), normalizedVoltage.astype(np.int16))

duration = 30
df = pd.read_csv('data/datas.csv')

times = np.array(df["Times"].tolist())
datas = np.array(df["Values"].tolist())

# filter data to a ranges
filterIndex = np.logical_and(datas > 50, datas < 200)
filteredTimes = times[filterIndex]
filterDatas = datas[filterIndex]


fRatio = 1
datasFt = np.fft.fft(filterDatas)
datasMag = np.abs(datasFt)
frequency = np.linspace(0,len(filterDatas)/duration,len(datasMag))
freqBin = int(len(frequency)*fRatio)

domain = frequency > 10


plt.subplot(2, 1, 1)
plt.plot(filteredTimes, filterDatas)

plt.subplot(2, 1, 2)
plt.plot(frequency[domain], datasMag[domain])
plt.show()


