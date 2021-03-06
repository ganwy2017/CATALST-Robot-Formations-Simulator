//
// Filename:        "Environment.h"
//
// Programmer:      Ross Mead
// Last modified:   30Nov2009
//
// Description:     This class describes a robot cell environment.
//

// preprocessor directives
#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H
#include <queue>
#include <time.h>
#include <vector>
#include <stack>
#include <fstream>
#include "Cell.h"
#include "Log.h"
using namespace std;



//
#define VERBOSE (0)
#define QUIESCENCE_COUNT (5)
#define INSERTION_RANDOM (0)
#define PUSH_RANDOM (0)



// global constants
static const Color DEFAULT_ENV_COLOR = BLACK;



// describes a robot cell environment
class Environment
{
    public:

        // <public data members>
        GLfloat color[3];
        bool    startFormation;
        GLint   formationID;

        // <constructors>
        Environment(const GLint     n          = 0,
                    const Formation f          = Formation(),
                    const Color     colorIndex = DEFAULT_ENV_COLOR,
                    const int       insertion  = 0,
                    const float     max_t_error = MAX_TRANSLATIONAL_ERROR,
                    string          randInput = "randOut.txt");
        Environment(const Environment &e);

        // <destructors>
        virtual ~Environment();

        // <virtual public mutator functions>
        virtual bool setColor(const GLfloat r,
                              const GLfloat g,
                              const GLfloat b);
        virtual bool setColor(const GLfloat clr[3]);
        virtual bool setColor(const Color colorIndex = DEFAULT_VECTOR_COLOR);

        // <public mutator functions>
        bool addCell(Cell *c = NULL);
        bool removeCell();
        bool removeCell(Cell* c);
        bool addRobot(GLfloat x     = 0.0f, GLfloat y = 0.0f, GLfloat z = 0.0f,
                      GLfloat theta = 0.0f);
        bool removeRobot(Robot* r);

        // <public accessor functions>
        Cell*               getCell(GLint pos) const;
        Robot*              getRobot(GLint id);
        vector<Cell *>  getCells();
        vector<Robot *> getRobots();
        GLint               getNCells() const;
        GLint               getNFreeRobots() const;


        // <virtual public utility functions>
        virtual void draw();
        virtual bool step();
        virtual void clear();

        // <public utility functions>
        Vector  getRelationship(const GLint toID, const GLint fromID);
        GLfloat getDistanceTo(const GLint id)   const;
        GLfloat getAngleTo(const GLint id)      const;
		//removed const from parameters
        bool    sendMsg(const Message &msg = NULL,
                        const GLint    toID   = ID_BROADCAST,
                        const GLint    fromID = ID_OPERATOR,
                        const GLint    type   = HEARTBEAT);

		//removed const
        bool    sendPacket(const Packet &p = Packet());
        vector<Cell *>  getCellVector();
        vector<Robot *> getRobotVector();

		//removed const
        bool    forwardPacket(const Packet &p);
        bool    forwardPackets();

        // <public utility cell functions>
        bool    showLine(const bool show);
        bool    showHead(const bool show);
        bool    showPos(const bool show);
        bool    showHeading(const bool show);
        bool    useInsertion();
        void    testCellNaN(Cell * c);


        // <public utility auctioning functions>
        //bool    auctionPosition(Cell* a);
        Robot*  getNearestRobot(Cell *c);
        Robot*  getNearestRobot(GLfloat x, GLfloat y);
        GLfloat distanceToRobot(Cell *c,Robot *r);
        GLfloat distanceToRobot(GLfloat x,GLfloat y,Robot *r);
        void    formUp();
        void    formFromClick(GLfloat x,GLfloat y);
        bool    changeFormation(Formation &f);
        void    settlePushAuction(Cell* c,GLint bID);
        void    settleInsertionAuction(Robot* c,GLint bID);
        void    writeDistanceData(char * filename,char * filename2);
        void    displayStateOfEnv();
        int     getHopCount(Cell * c, Direction d);    // set direction to true for hop count down the rightNbr and false for the leftNbr
        void    displayNeighborhood(Cell * c);
        void    dieDisplayCells();
        void    insertCell(Cell* a, Cell *b, Cell* c);
        void    dumpMessagesToFile(char * filename);
        void    gatherMessages();
        void    gatherError();
        void    gatherDistances();
        void    gatherConvergence();
        void    dumpErrorToFile(char * filename);
        bool    quiescence();
        void    writeHeader();
        void    writeFinalPositions();

        //ostream &st);
        //void    summaryReport(ostream &os);
        int     stepCount;
    protected:

        // <protected data members>
        vector<Cell *>          cells;
        vector<Robot *>         robots;
        queue<Packet>           msgQueue;
        queue<float>           initLocs;
        queue<Cell *>           auctions;
        Cell                    *newestCell;
        Formation               formation;
        GLint                   nRobots;
        Color                   defaultColor;
        int                     insertion;
        int                     totalMessages;
        vector<Message_Log>     allMessages;
        vector<Packet>          messagesPerStep;
        vector<Error_Log>       errorSum;
        vector<Distances_Log>   totalDistances;

        int                     qCount;
        string                  inputFile;
        float                   max_trans_error;
        bool                    perfect;

        //stats

        float   overallDistance;


        // <virtual protected utility functions>
        virtual bool init(const GLint     n          = 0,
                          const Formation f          = Formation(),
                          const Color     colorIndex = DEFAULT_ENV_COLOR,
                          const int       insert     = 0,
                          const float     max_t_error = MAX_TRANSLATIONAL_ERROR);
        //virtual bool initCells(const GLint     n = 0,
        //                       const Formation f = Formation());
        //virtual bool initNbrs(const GLint nNbrs = 0);
		virtual bool initRobots();
};  // Environment

#endif
