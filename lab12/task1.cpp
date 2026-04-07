#include <iostream>
#include <string>

using namespace std;

class AudioCodec {
public:
    virtual void decode(const string& fileName) = 0;
    virtual ~AudioCodec() {}
};

class MP3Codec : public AudioCodec {
    public:
    void decode(const string& fileName) override {
        cout << "Playing " << fileName << " using MP3 codec." << endl;
    }
};

class WAVCodec : public AudioCodec {
    public:
    void decode(const string& fileName) override {
        cout << "Playing " << fileName << " using WAV codec." << endl;
    }
};

class FLACCodec : public AudioCodec {
    public:
    void decode(const string& fileName) override {
        cout << "Playing " << fileName << " using WAV codec." << endl;
    }
};

class MusicPlayer {
protected:
    AudioCodec* codec;
public:
    MusicPlayer(AudioCodec* c) : codec(c) {}
    virtual void start(const string& fileName) = 0;
    virtual ~MusicPlayer() {}
};

class PopPlayer : public MusicPlayer {
    public:
    PopPlayer(AudioCodec* c) : MusicPlayer(c) {}

    void start(const string& fileName) override {
        cout << "Started Pop Player..." << endl;
        codec->decode(fileName);
    }
};

class JazzPlayer : public MusicPlayer {
    public:
    JazzPlayer(AudioCodec* c) : MusicPlayer(c) {}

    void start(const string& fileName) override {
        cout << "Started Jazz Player..." << endl;
        codec->decode(fileName);
    }
};

class RockPlayer : public MusicPlayer {
    public:
    RockPlayer(AudioCodec* c) : MusicPlayer(c) {}

    void start(const string& fileName) override {
        cout << "Started Rock Player..." << endl;
        codec->decode(fileName);
    }
};


int main() {
    // Using pointers for polymorphism
    AudioCodec* mp3 = new MP3Codec();
    AudioCodec* wav = new WAVCodec();
    AudioCodec* flac = new FLACCodec();

    MusicPlayer* pop= new PopPlayer(mp3);
    MusicPlayer* jazz= new JazzPlayer(mp3);
    MusicPlayer* rock= new RockPlayer(mp3);

    pop->start("pop_song_1.mp3");
    jazz->start("jazz_song.mp3");
    rock->start("pop_song_2.wav");

    // Clean up
    delete pop;
    delete jazz;
    delete rock;
    delete wav;
    delete mp3;
    delete flac;

    return 0;
}
