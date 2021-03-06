#ifndef MIDIFILE_H
#define MIDIFILE_H

#include "MidiEvent.h"

#include <QString>
#include <QList>
#include <QFile>

class MidiFile
{
public:
    enum DivisionType {
        Invalid = -1,
        PPQ = 0,
        SMPTE24 = -24,
        SMPTE25 = -25,
        SMPTE30DROP = -29,
        SMPTE30 = -30
    };

    MidiFile();
    ~MidiFile();

    void clear();
    bool read(const QString &file, bool seekFileChunkID = false);
    bool read(QFile *in, bool seekFileChunkID = false);

    int formatType() { return fFormatType; }
    int numberOfTracks() { return fNumOfTracks; }
    int resorution() { return fResolution; }
    DivisionType divisionType() { return fDivision; }
    QList<MidiEvent*> events() { return fEvents; }
    QList<MidiEvent*> tempoEvents() { return fTempoEvents; }
    QList<MidiEvent*> controllerEvents() { return fControllerEvents; }
    QList<MidiEvent*> programChangeEvents() { return fProgramChangeEvents; }
    QList<MidiEvent*> timeSignatureEvents() { return fTimeSignatureEvents; }
    QList<MidiEvent*> controllerAndProgramEvents();

    MidiEvent* createMidiEvent(int track, uint32_t tick, uint32_t delta, MidiEventType evType, int ch, int data1, int data2);
    MidiEvent* createMetaEvent(int track, uint32_t tick, uint32_t delta, int number, QByteArray data);
    MidiEvent* createSysExEvent(int track, uint32_t tick, uint32_t delta, QByteArray data);

    float    beatFromTick(uint32_t tick);
    float    timeFromTick(uint32_t tick, int bpmSpeed = 0);
    uint32_t tickFromTime(float time, int bpmSpeed = 0);
    uint32_t tickFromTimeMs(long msTime, int bpmSpeed = 0);

    static int firstBpm(const QString &file);
    static int firstBpm(QFile *in);

private:
    int fFormatType;
    int fNumOfTracks;
    int fResolution;
    DivisionType fDivision;
    QList<MidiEvent*> fEvents;
    QList<MidiEvent*> fTempoEvents;
    QList<MidiEvent*> fControllerEvents;
    QList<MidiEvent*> fProgramChangeEvents;
    QList<MidiEvent*> fTimeSignatureEvents;
};

#endif // MIDIFILE_H
