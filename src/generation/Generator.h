#ifndef SAG_GENERATOR_H
#define SAG_GENERATOR_H

#include "utils/types.h"
#include "utils/Bounds.h"
#include "utils/Particle.h"
#include "formulas/Formula.h"
#include "rendering/Renderer.h"

namespace sag {
    /**
     * @brief The abstract Generator class.
     *
     * The Generator moves Particles around while looping.
     * In addition, it also kills them sometimes. They are reborn though.
     * It's that simple.
     */
	class Generator {
	public:
        /**
         * @param Constructs a Generator using a Formula and a Renderer.
         *
         * @param f The formula to use for generating.
         * @param r The renderer to send the particles to.
         * @param iter The desired iteraction count.
         * @param if3D (optional) True if it should go 3D.
         */
		Generator(Formula& f, Renderer& r, int iter, bool if3D=false);
		
		virtual ~Generator() {}

        /**
         * @brief Starts the generating engines.
         */
		virtual void run() = 0;
        
        static const int UNLIMITED_ITERATIONS = -1;
        static const int IMMORTAL_PARTICLES = 0;
        
        /**
         * @brief Sets the particle count.
         *
         * There can exist multiple particles at the same time. Use this method to specify how many.
         */
        void setParticleCount(int pc);
        
        /**
         * @brief Sets the Time To Live.
         *
         * TTL determines after how many iterations should a generation of particles die 
         * (and be reborn in a different place).
         *
         * @param ttl Time To Live. At least 2, or else it wouldn't make sense.
         */
        void setTTL(int ttl);
        
        /**
         * @brief Resets the Generator.
         *
         * Randomizes the Formula and makes a clean start.
         */
        void reset();
        
        /**
         * @brief Aborts the Generator.
         */
		void abort();
		
        /**
         * @brief Returns the bounds of the particle system.
         *
         * @returns Bounds.
         */
		inline Bounds<number> getBounds() const { return bounds; }
		
        /**
         * @brief Checks if we are 3D.
         *
         * @returns True of false.
         */
		inline bool is3D() { return if3D; }

	protected:
		Formula *formula;
		Bounds<number> bounds;
		int particleCount;
		const bool if3D;
        volatile bool running;
        int iterations;
        int ttl;
		Renderer *renderer;

        /**
         * @brief Sends a Particle to the Renderer.
         *
         * @param p A Particle.
         */
		void sendParticle(const Particle& p);
		
	private:
		static const int WARMUP_ITERATIONS = 5000;

		void setBounds();
	};
}

#endif
